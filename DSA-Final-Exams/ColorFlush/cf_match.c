#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct _s_match
{
    node cards;
    unsigned int size;
};

struct _s_node_match
{
    card elemCard;
    node nextCard;
};

node new_node(card c)
{
    node nodi = malloc(sizeof(struct _s_node_match));
    nodi->elemCard = c;
    nodi->nextCard = NULL;
    return nodi;
}

cf_match match_new(void)
{
    cf_match match = malloc(sizeof(struct _s_match));
    match->cards = NULL;
    match->size = 0;
    return match;
}

cf_match match_add(cf_match match, card c)
{

    
    node newNode = new_node(c);

    if(match_size(match) == 0)
    {
        match->cards = newNode;
    }
    else
    {
        node auxNode = match->cards;
        while (auxNode->nextCard != NULL)
        {
            auxNode = auxNode->nextCard;
        }

        auxNode->nextCard = newNode;
    }
    match->size++;
    return match;
}

unsigned int match_size(cf_match match)
{
    return match->size;
}

bool is_match_correct(cf_match match)
{
    assert(match->cards->elemCard != NULL);
    node aux_node = match->cards;
    if (card_player(match->cards->elemCard) != 1 || (match_size(match)) % 2 != 0)
        return false;
    for (unsigned int i = 0u; i < match_size(match) - 1; i++)
    {
        if (card_player(aux_node->elemCard) == card_player(aux_node->nextCard->elemCard) || card_color(aux_node->elemCard) == card_color(aux_node->nextCard->elemCard))
            return false;
        aux_node = aux_node->nextCard;
    }
    return true;
}

static int player_score(cf_match match, unsigned int player)
{
    
    bool is_flushed = false, is_uppwards = false;
    int score = 0;
    node aux_node = match->cards;
    if (player == 2 && aux_node != NULL && aux_node->nextCard!= NULL )
    {
        score = card_drop_points(aux_node->elemCard, aux_node->nextCard->elemCard, is_flushed, is_uppwards);
        aux_node = aux_node->nextCard;
    }
    while(aux_node != NULL && aux_node->nextCard!= NULL )
    {
        if (card_number(aux_node->elemCard) == card_number(aux_node->nextCard->elemCard) 
        || card_number(aux_node->elemCard) == card_number(aux_node->nextCard->elemCard) - 1
        || card_number(aux_node->elemCard) == card_number(aux_node->nextCard->elemCard) + 1)
        {
            if (card_player(aux_node->nextCard->elemCard) == player){
                score = score + card_drop_points(aux_node->elemCard, aux_node->nextCard->elemCard, is_flushed, is_uppwards);
            }
            is_flushed = true;
            is_uppwards = card_number(aux_node->elemCard) < card_number(aux_node->nextCard->elemCard);
        }
        else
        {
            is_flushed = false;
            is_uppwards = false;
        }
        aux_node = aux_node->nextCard;
        if(aux_node->nextCard != NULL){
            if (card_player(aux_node->nextCard->elemCard) == player)
            {
               score = score + card_drop_points(aux_node->elemCard, aux_node->nextCard->elemCard, is_flushed, is_uppwards);
               aux_node = aux_node->nextCard;
            }
        }
    }
    return score;
}

unsigned int match_winner(cf_match match)
{
    unsigned int winner;

    if (!is_match_correct(match))
    {
        return -1;
    }

    if (player_score(match, 1) > player_score(match, 2))
    {
        winner = 1;
    }
    else if (player_score(match, 1) < player_score(match, 2))
    {
        winner = 2;
    }
    else if(player_score(match, 1) == player_score(match, 2))
    {
        winner = 0;
    }
    return winner;
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match))
    {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore)
    {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card *match_to_array(cf_match match)
{
    card *array = calloc(match_size(match), sizeof(card));
    node aux_node = match->cards;
    for (unsigned int i = 0u; i < match_size(match); i++)
    {
        array[i] = aux_node->elemCard;//card_new(card_number(aux_node->elemCard), card_suit(aux_node->elemCard), card_player(aux_node->elemCard));
        aux_node = aux_node->nextCard;
    }
    return array;
}

void match_dump(cf_match match)
{
    card *array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++)
    {
        card_dump(array[i]);
    }
    for(unsigned int i=0u; i<match_size(match); i++){
        array[i] = card_destroy(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
    node aux_node= match->cards;
    while (aux_node != NULL)
    {
        node killme = NULL;
        killme = aux_node;
        aux_node = aux_node->nextCard;
        free(killme);
    }
    free(match);
    match = NULL;
    return match;
}
