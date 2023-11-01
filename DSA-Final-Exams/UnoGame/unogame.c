#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    card_t * cards;
    player_t act_play;
    unsigned int capacity;
    unsigned int size;
};

unogame_t uno_newgame(card_t card) {
    unogame_t start = malloc(sizeof(struct s_ugame));
    start->cards = calloc(2, sizeof(card_t));
    start->cards[0] = card;
    start->size = 1;
    start->capacity = 2;
    start->act_play = NO_PLAYER;
    return start;
}

card_t
uno_topcard(unogame_t uno) {
    return uno->cards[uno->size-1];
}

unogame_t uno_addcard(unogame_t uno, card_t c) {
   
        uno->act_play = uno_nextplayer(uno);
        if(uno->capacity == uno->size){
            uno->capacity = 2*(uno->capacity);
            uno->cards = realloc(uno->cards, uno->capacity * sizeof(card_t));
        }
        uno->size++;
        uno->cards[uno->size-1] = c;
        
    
    return uno;
}



unsigned int uno_count(unogame_t uno) {
    return uno->size; 
}

bool uno_validpile(unogame_t uno) {
    bool valid = true;
    if(card_get_type(uno->cards[0]) == change_color){
        return false;
    }

    for(unsigned int i = 1; i < uno_count(uno); i++){
        if(!card_compatible(uno->cards[i-1], uno->cards[i])){
            return false;
        }
    }
    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    return card_get_color(uno->cards[uno->size -1]);  
}

player_t uno_nextplayer(unogame_t uno) {
    player_t next_play = 0;
    
    if(card_get_type(uno->cards[uno_count(uno)-1]) != skip){
        if(uno->act_play < NUM_PLAYERS-1){
            next_play = uno->act_play+1;
        } else{
            next_play = 0;
        }
    }else{
        if(uno->act_play < NUM_PLAYERS-2){
            next_play = uno->act_play+2;
        } else{
            if(uno->act_play > NUM_PLAYERS-2){
                next_play = 1;
            } else{
                next_play = 0;
            }
        }
    }
    
    return next_play;
}



card_t * uno_pile_to_array(unogame_t uno) {
    card_t *copy = calloc(uno->size, sizeof(card_t));
    unsigned int count=0;
    while(count < uno->size){
        copy[count] = card_new(card_get_number(uno->cards[count]),card_get_color(uno->cards[count]), card_get_type(uno->cards[count]));
        count++;
    }
    return copy;
}

unogame_t
uno_destroy(unogame_t uno) {
    for(int i = uno->size -1; i >= 0 ; i--){
      uno->cards[i] = card_destroy(uno->cards[i]);
    }
    free(uno->cards);
    free(uno);
    uno = NULL;
    return NULL;
}

