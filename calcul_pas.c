#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mt.h"

// fonction récursive, effectue un pas de calcul et rapelle la fonction tant qu'il reste des transitions valables renvoie 0 si tout a bien fonctionné
int calcul_pas(MT ma_machine, CARREAU tete_lecture)
{
    ///////////////////////
    sleep(1);
    // Clean le terminal
    printf("\e[1;1H\e[2J");
    //
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

    int i = 0;
    int j = 0;
    int cpt = 0;
    TRANSI actuelle = ma_machine->liste_transitions->premier;

    while (actuelle) // Parcourt toutes les transitions pour en trouver une qui correspond à l'état actuel et au caractère lu
    {
        if ((!strcmp(actuelle->ma_transition.etat_lu, ma_machine->etat_courant)) && (actuelle->ma_transition.caractere_lu == tete_lecture->valeur))
        {
            j = i;
            cpt++;
        }
        actuelle = actuelle->suiv;
        i++;
    }

    if (cpt > 1) // On en a trouvé plus d'une il y'a donc ambiguëté
    {
        printf("Erreur, ambiguité dans vos transitions \n");
        return 1;
    }
    
    actuelle = ma_machine->liste_transitions->premier;
    if (cpt == 1)
    {
        for (int i = 0; i < j; i++)
        {
            actuelle = actuelle->suiv;
        }

        strcpy(ma_machine->etat_courant, actuelle->ma_transition.nouvel_etat);
        tete_lecture->valeur = actuelle->ma_transition.nouveau_caractere;

        switch (actuelle->ma_transition.direction)
        {
        case '>':
            if (tete_lecture == ma_machine->etat_bande->dernier)
            {
                // On est à la fin du ruban on ajoute _ par précaution pour que nos transitions fonctionnent bien
                ajout_elem(ma_machine->etat_bande, '_');
            }

            tete_lecture = tete_lecture->suiv;
            ma_machine->position_tete_lecture++;
            break;

        case '<':
            if (!ma_machine->position_tete_lecture) // position de la tête de lecture = 0 donc lorsque l'on est au tout début on bloque l'accès car le ruban n'est pas bi infini
            {
                printf("Le ruban n'est pas bi infini vous ne pouvez pas aller à gauche ! \n");
                return 1;
            }

            tete_lecture = tete_lecture->prec;
            ma_machine->position_tete_lecture--;
            break;

        case '-':
            break;

        default:
            printf("Erreur dans les transitions, mauvais symboles de direction.\n");
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
