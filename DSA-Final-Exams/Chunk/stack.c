#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    struct s_node * next;
    stack_elem * array;
    unsigned int used;
};

struct _s_stack {
    struct s_node *top;
    unsigned int size;
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check = s->top;
    valid = check != NULL;
    return valid;
}

static bool
invrep(stack s) {
    bool valid;
    struct s_node * aux_node = s->top;
    if(valid_chunks(s)){
        for(unsigned int i=0; i<s->size; i++){
            valid = aux_node->used != 0;
            aux_node = aux_node->next;
        }
    }else{
        return false;
    }
    return (valid && s!=NULL);
}

static struct s_node *
create_node(void) {
    struct s_node * new_node = NULL;

    new_node = malloc(sizeof(struct s_node));
    new_node->array = calloc(5, sizeof(stack_elem));;
    new_node->used = 0; // 5 max
    return new_node;
}


static struct s_node *
destroy_node(struct s_node *node) {
    free(node->array);    
    free(node);
    node = NULL;
    return node;
}

stack stack_empty(void) 
{
    
    stack new_stack = malloc(sizeof(struct _s_stack));
    new_stack->size = 0;
    new_stack->top = NULL;
    return new_stack;
    assert(invrep(new_stack) && stack_is_empty(new_stack));
}


stack stack_push(stack s, stack_elem e) {
    
    
    if(s->top == NULL){
        struct s_node* newNode = create_node();
        newNode->next = NULL;
        newNode->used = 1;
        newNode->array[0] = e;
        s->top = newNode;
         
    } else if(s->top->used == 5){
        struct s_node* newNode = create_node();
        newNode->next = NULL;
        newNode->used = 1;
        newNode->array[0] = e;
        struct s_node * auxNode = s->top;
        newNode->next = auxNode;
        s->top = newNode;
    }else{
        s->top->array[s->top->used] = e;
        s->top->used++; 
    }
    s->size++;
    return s;
    assert(invrep(s));
}


stack stack_pop(stack s) {
    if(!stack_is_empty(s)){
        struct s_node * auxNode = s->top;
        if(auxNode->used > 1){
            auxNode->array[auxNode->used-1] = ' ';
            auxNode->used--;
        }else{
            struct s_node * killme = s->top;
            s->top = s->top->next;
            killme = destroy_node(killme);
        }
        s->size--;
    }
    
    return s;
}


unsigned int stack_size(stack s) {
    assert(invrep);
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    assert(invrep);
    *top = s->top->array[s->top->used-1];
}

bool stack_is_empty(stack s) {
    return s->size == 0;
}

stack_elem *stack_to_array(stack s) {
    stack_elem *s_t_array = calloc(stack_size(s), sizeof(stack_elem));
    struct s_node * auxNode = s->top;
    unsigned int count = 0, i = stack_size(s)-1;
    while(auxNode != NULL){
        if(auxNode->used > count){
            s_t_array[i] = auxNode->array[(s->top->used-1) - count];
            count++;
        }else{
            auxNode = auxNode->next;
        }
        i--;
    }
    return s_t_array;
}


stack stack_destroy(stack s) {

    while(s->top != NULL){
        s = stack_pop(s);
    }
    free(s);
    s = NULL;
    return s;    
}

