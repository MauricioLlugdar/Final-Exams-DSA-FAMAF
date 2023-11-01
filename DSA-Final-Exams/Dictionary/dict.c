#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* interface           */

struct _s_dict {
    unsigned int size;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {
    
    return dict != NULL;
}
// --- Interface functions ---

dict_t dict_empty(void) {

    dict_t dict = malloc(sizeof(struct _s_dict));
    dict->first = NULL;
    dict->size = 0;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    struct _node_t *newNode = create_node(word, def);
    if(dict->first == NULL){
        dict->first = newNode;
    }else{
        struct _node_t *auxNode = dict->first;

        while(auxNode->next != NULL){
            auxNode = auxNode->next;
        }
        auxNode->next = newNode;
    }
    dict->size++;
    assert(invrep(dict));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    value_t val = NULL;
    struct _node_t * auxNode = dict->first;
    if(dict_exists(dict, word)){
        while(!key_eq(auxNode->key,word)){
            auxNode = auxNode->next;
        }
        val = auxNode->value;
    }
    assert(invrep(dict));
    return val;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool b = false;
    if(dict_length(dict) != 0){
        struct _node_t * auxNode = dict->first;
        while(!key_eq(auxNode->key, word) && auxNode->next != NULL){
            auxNode = auxNode->next;
        }
        b = key_eq(auxNode->key, word);
    }
    assert(invrep(dict));
    return b; 

}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    return dict->size;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if(dict_exists(dict, word) && dict_length(dict) >0){
        struct _node_t * auxNode = dict->first;
        struct _node_t * killme;
        if(key_eq(auxNode->key,word)){
            killme = auxNode;
            auxNode = auxNode->next;
            killme = destroy_node(killme);
        }else{
            while(!key_eq(auxNode->next->key, word)){
                auxNode = auxNode->next;
            }
            killme = auxNode;
            auxNode = auxNode->next;
            killme = destroy_node(killme);
        }
        dict->size--;
    }
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if(dict->size >0){
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
    }
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict->size >0){
    struct _node_t * auxNode = dict->first;
    struct _node_t * killme;
    while(auxNode != NULL){
        killme = auxNode;
        auxNode = auxNode->next;
        killme = destroy_node(killme);
        dict->size--;
    }
    }
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

