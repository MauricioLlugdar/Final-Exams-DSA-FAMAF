#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
        position_t iniPos= calloc(1, sizeof(struct _position));
        iniPos->dimension = dimension;
        return iniPos;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        assert(row < dimension && column < dimension);
        position_t actPos = malloc(sizeof(struct _position));
        actPos->column = column;
        actPos->dimension = dimension;
        actPos->row = row;
        return actPos;
}

position_t position_left(position_t pos)
{
        //Lets move to the left
        if(position_column(pos) > 0){
                pos->column--;
        }else{
                pos->column = pos->dimension-1;
        }
        return pos;
}

position_t position_right(position_t pos)
{
        if(position_column(pos) < pos->dimension-1){
                pos->column++;
        }else{
                pos->column = 0;
        }
        return pos;
}

position_t position_down(position_t pos)
{
        if(position_row(pos) < pos->dimension-1){
                pos->row++;
        } else{
                pos->row = 0;
        }
        return pos;
}

position_t position_up(position_t pos)
{
        if(position_row(pos) > 0){
                pos->row--;
        } else{
                pos->row = pos->dimension-1;
        }
        return pos;
}

unsigned int position_row(position_t pos)
{
        return pos->row;
}

unsigned int position_column(position_t pos)
{
        return pos->column;
}

unsigned int ** position_board(position_t pos)
{
        unsigned int ** matrix = calloc((pos->dimension), sizeof(unsigned int*));
        for(unsigned int i=0; i<pos->dimension;i++){
                matrix[i] = calloc((pos->dimension), sizeof(unsigned int));
        }
        matrix[position_row(pos)][position_column(pos)] = 1;
        return matrix;        
}

unsigned int ** destroy_matrix(unsigned int ** matrix, unsigned int dimension){
        for(unsigned int i=0; i<dimension; i++){
                free(matrix[i]);
        }
        free(matrix);
        matrix = NULL;
        return matrix;
}

void dump_matrix(unsigned int ** matrix, unsigned int dimension){
        unsigned int count1=0, count2=0;

        while (count1 < dimension)
        {       
                count2=0;
                
                while (count2 < dimension)
                {
                        if(count2 == 0){
                                printf(" ");
                        }
                        printf("[%u]", matrix[count1][count2]);
                        if(count2 != dimension-1){
                                printf(" ");
                        }
                        count2++;
                }
                printf("\n");
                count1++;
        }
        

}

list_t position_movements(position_t pos)
{
        unsigned int count1 = 0, count2 = 0;
        list_t movs = list_empty();
        while (count1 < position_column(pos))
        {
                movs = list_append(movs, RIGHT);
                count1++;
        }
        while(count2 < position_row(pos)){
                movs = list_append(movs, DOWN);
                count2++;
        }

        return movs;
        
}

position_t position_destroy(position_t pos)
{
        free(pos);
        pos = NULL;
        return pos;
}
