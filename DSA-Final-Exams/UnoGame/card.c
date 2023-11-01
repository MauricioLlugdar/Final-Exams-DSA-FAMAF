#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    valid = (c->num < 10) && (c->color==red || c->color==green || c->color==blue || c->color==yellow) && (c->type==normal  || c->type==change_color || c->type==skip);
    return valid;
}

card_t card_new(unsigned int num, color_t color, type_t s) {
    assert((num < 10) && (color==red || color==green || color==blue || color==yellow) 
    && (s==normal  || s==change_color || s==skip));
    card_t card=NULL;
    card = malloc(sizeof(struct s_card));
    card->color = color;
    card->type = s;
    card->num = num;
    assert(invrep);
    return card;
}


type_t card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool card_samecolor(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return c1->color == c2->color;
}


bool
card_samenum(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return c1->num == c2->num;
}

bool
card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));
    if(card_samecolor(new_card, pile_card)){
        return true;
    } else if(new_card->type == change_color){
        return true;
    } else if(new_card->type == normal && pile_card->type == normal){
        if(card_samenum(new_card, pile_card)){
            return true;
        }
    } else if(new_card->type == skip && pile_card->type == skip){
        return true;
    } else if(new_card->type == change_color){
        return true;
    }
    return compatible;
}

card_t
card_destroy(card_t card) {
    assert(invrep(card));
    free(card);
    card = NULL;
    assert(card == NULL);
    return NULL;
}


