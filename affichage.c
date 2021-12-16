#include <stdio.h>
#include "mt.h"


void affiche_transition(T *tab_transition, int nb_transitions)
{
    for (int i = 0; i < nb_transitions; i++)
    {
        printf("%s, %c \n", tab_transition[i].etat_lu, tab_transition[i].caractere_lu);
        printf("%s, %c, %c \n", tab_transition[i].nouvel_etat, tab_transition[i].nouveau_caractere, tab_transition[i].direction);
    }
}

void affiche_bandeau(BANDEAU b)
{
    CARREAU affichage = b->premier;
    while (affichage)
    {
        printf("%c ", affichage->valeur);
        affichage = affichage->suiv;
    }
    printf("\n");
}