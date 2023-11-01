#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"
int main()
{
    unsigned int dimension;
    printf("Crearemos una matriz, en donde se podrá colocar un elemento\n");
    printf("Ingresar la dimensión de la matriz: ");
    scanf("%u", &dimension);
    position_t actPos = position_initial(dimension);
    //Probado con pos abs.cambiar pos ini
    unsigned int ** matrix = position_board(actPos);
    list_t movs = list_empty();

    dump_matrix(matrix, dimension);

    movs = position_movements(actPos);

    list_show(movs);

    actPos = position_destroy(actPos);
    movs = list_destroy(movs);
    matrix = destroy_matrix(matrix, dimension);

    return 0;
}