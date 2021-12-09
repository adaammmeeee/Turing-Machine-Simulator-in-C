#include <stdio.h>
#include "mt.h"

void init(BANDEAU b){
    b->first = NULL; 
    b->last = NULL;
}

int ajout_elem(BANDEAU b, char elem){
    CARREAU new = malloc(sizeof(struct carreau));
    if (!new) {
        return 1;
    }
    
    if (!b->last) { // Le bandeau est vide
        new->value = elem;
        new->prev = NULL;
        new->next = NULL;
        b->last = new;
        b->first = new;
    }
    else { //Bandeau pas vide
        new->value = elem;
        new->prev = b->last;
        new->next = NULL;
        b->last->next = new;
        b->last = new;
    }

    
 


}