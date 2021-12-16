#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mt.h"

int calcul_pas(MT ma_machine, CARREAU tete_lecture)
{

    ///////////////////////
    sleep(1);
    printf("\e[1;1H\e[2J");
    if (ma_machine->position_tete_lecture == 0)
    {
        printf("\n\n");
        affiche_bandeau(ma_machine->etat_bande);
        printf("^\n");
        printf("Position de la tête de lecture : %d\n", ma_machine->position_tete_lecture + 1);
        printf("Etat courant : %s\n", ma_machine->etat_courant);
    }
    else
    {
        printf("\n\n");
        affiche_bandeau(ma_machine->etat_bande);

        for (int i = 0; i < ma_machine->position_tete_lecture; i++)
        {
            printf("  ");
        }

        printf("^\n");
        printf("Position de la tête de lecture : %d\n", ma_machine->position_tete_lecture + 1);
        printf("Etat courant : %s\n", ma_machine->etat_courant);
    }

    ///////////////////////

    int j = 0;
    int cpt = 0;
    for (int i = 0; i < ma_machine->nb_transitions; i++)
    {
        // printf("%c   %c \n", ma_machine->tab_transitions[i].etat_lu, ma_machine->tab_transitions[i].caractere_lu);
        if ((!strcmp(ma_machine->tab_transitions[i].etat_lu, ma_machine->etat_courant)) && (ma_machine->tab_transitions[i].caractere_lu == tete_lecture->valeur))
        {
            j = i;
            cpt++;
        }
    }

    if (cpt > 1)
    {
        printf("Erreur, ambiguité dans vos transitions \n");
        return 1;
    }

    if (cpt == 1)
    {
        strcpy(ma_machine->etat_courant, ma_machine->tab_transitions[j].nouvel_etat);
        tete_lecture->valeur = ma_machine->tab_transitions[j].nouveau_caractere;

        switch (ma_machine->tab_transitions[j].direction)
        {
        case '>':
            if (tete_lecture == ma_machine->etat_bande->dernier)
            {
                ajout_elem(ma_machine->etat_bande, '_');
            }

            tete_lecture = tete_lecture->suiv;
            ma_machine->position_tete_lecture++;
            break;

        case '<':
            if (!ma_machine->position_tete_lecture)
            {
                printf("Le ruban n'est pas bi infini vous ne pouvez pas aller à droite! \n");
                return 1;
            }

            tete_lecture = tete_lecture->prec;
            ma_machine->position_tete_lecture--;
            break;

        case '-':
            break;

        default:
            printf("Erreur dans les transitions, mauvais symboles de directions.\n");
            return 2;
        }

        return calcul_pas(ma_machine, tete_lecture);
    }

    if (cpt == 0)
    {
        if (!strcmp(ma_machine->etat_courant, ma_machine->etat_accepte))
        {
            printf("Accepté ! \n");
            return 0;
        }
        else
        {
            printf("Non accepté ! \n");
            return 0;
        }
    }
    return 0;
}
