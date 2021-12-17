#include <stdlib.h>
#include <stdio.h>
#include "mt.h"





// Initialise la structure bandeau
void init(BANDEAU b)
{
    b->premier = NULL;
    b->dernier = NULL;
}

// Ajoute une case de valeur "elem" à la fin du bandeau
int ajout_elem(BANDEAU b, char elem)
{
    CARREAU new = malloc(sizeof(struct carreau));
    if (!new)
    {
        return 1;
    }

    if (!b->dernier)
    { // Le bandeau est vide
        new->valeur = elem;
        new->prec = NULL;
        new->suiv = NULL;
        b->dernier = new;
        b->premier = new;
    }
    else
    { // Bandeau pas vide
        new->valeur = elem;
        new->prec = b->dernier;
        new->suiv = NULL;
        b->dernier->suiv = new;
        b->dernier = new;
    }
    return 0;
}

void init_liste_transi(LISTE_TRANSI liste_transition)
{
    liste_transition->premier = NULL;
    liste_transition->dernier = NULL;
}

int ajout_transition(LISTE_TRANSI liste_transition, T ma_transition)
{
    TRANSI new = malloc(sizeof(struct elem_transition));
    if (!new)
    {
        return 1;
    }

    if (!liste_transition->dernier)
    { 
        new->ma_transition = ma_transition;
        new->prec = NULL;
        new->suiv = NULL;
        liste_transition->dernier = new;
        liste_transition->premier = new;
    }
    else
    { 
        new->ma_transition = ma_transition;
        new->prec = liste_transition->dernier;
        new->suiv = NULL;
        liste_transition->dernier->suiv = new;
        liste_transition->dernier = new;
    }
    return 0;
}