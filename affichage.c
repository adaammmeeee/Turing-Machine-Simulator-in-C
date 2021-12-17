#include <stdio.h>
#include "mt.h"

void affiche_transition(MT ma_machine)
{
    TRANSI affichage = ma_machine->liste_transitions->premier;
    while (affichage)
    {
        printf("%s,%c\n%s,%c,%c\n\n", 
        affichage->ma_transition.etat_lu,
        affichage->ma_transition.caractere_lu, 
        affichage->ma_transition.nouvel_etat, 
        affichage->ma_transition.nouveau_caractere,
        affichage->ma_transition.direction);
        affichage = affichage->suiv;
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