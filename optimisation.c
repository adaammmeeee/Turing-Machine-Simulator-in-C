#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mt.h"

int remplace_suite_transition(MT ma_machine)
{

    int bool = 1;
    int cpt = 0;
    while (cpt < ma_machine->nb_transitions * ma_machine->nb_transitions) // pour chaque transition on va potentiellement reparcourir toutes les transitions donc ça nous fait n^2(n : nombre de transition)
    {
        TRANSI actuelle = ma_machine->liste_transitions->premier;
        T transition;
        transition.etat_lu = malloc(sizeof(char) * 10);
        transition.nouvel_etat = malloc(sizeof(char) * 10);

        TRANSI stock = ma_machine->liste_transitions->premier;
        int pos = 0;
        bool = 0;
        char buffer[20];
        char buffer1;
        while (actuelle) // On parcourt une première fois la boucle
        {
            if (actuelle->ma_transition.direction == '-')
            {

                strcpy(buffer, actuelle->ma_transition.nouvel_etat);
                buffer1 = actuelle->ma_transition.nouveau_caractere;

                transition.caractere_lu = actuelle->ma_transition.caractere_lu;
                strcpy(transition.etat_lu, actuelle->ma_transition.etat_lu);
                stock = actuelle;
                bool = 1;
            }
            pos++;

            actuelle = actuelle->suiv;
        }

        if (bool)
        {
            TRANSI actuelle2 = ma_machine->liste_transitions->premier;
            while (actuelle2) // On parcourt une seconde fois la bande pour savoir si la transition précedente est réellement utile
            {
                if ((!strcmp(actuelle2->ma_transition.etat_lu, buffer)) && (buffer1 == actuelle2->ma_transition.caractere_lu))
                {
                    strcpy(transition.nouvel_etat, actuelle2->ma_transition.nouvel_etat);
                    transition.nouveau_caractere = actuelle2->ma_transition.nouveau_caractere;
                    transition.direction = actuelle2->ma_transition.direction;
                    // On peut supprimer l'ancienne transition
                    if (pos == 1) // premier élément de la liste
                    {
                        ma_machine->liste_transitions->premier = stock->suiv;
                        free(stock->ma_transition.etat_lu);
                        free(stock->ma_transition.nouvel_etat);
                        free(stock);
                    }
                    if (pos == ma_machine->nb_transitions) // dernier élément de la liste
                    {
                        ma_machine->liste_transitions->dernier = stock->prec;
                        free(stock->ma_transition.etat_lu);
                        free(stock->ma_transition.nouvel_etat);
                        free(stock);
                    }
                    if ((pos != ma_machine->nb_transitions) && (pos != 1)) // au milieu de la liste
                    {
                        stock->prec->suiv = stock->suiv;
                        stock->suiv->prec = stock->prec;
                        free(stock->ma_transition.etat_lu);
                        free(stock->ma_transition.nouvel_etat);
                        free(stock);
                    }
                    bool = 2;
                    ajout_transition(ma_machine->liste_transitions, transition);
                }

                actuelle2 = actuelle2->suiv;
            }
            if (bool != 2)
            {
                bool = 0;
                free(transition.etat_lu);
                free(transition.nouvel_etat);
            }
        }
        cpt++;
    }
    return 0;
}

int code_mort(MT ma_machine)
{
    TRANSI actuelle = ma_machine->liste_transitions->premier;
    TRANSI actuelle2 = ma_machine->liste_transitions->premier;
    int bool = 0;
    int pos = 0;
    int pos2 = 0;
    while (actuelle)
    {
        pos++;

        actuelle2 = ma_machine->liste_transitions->premier;
        pos2 = 0;
        bool = 0;
        while (actuelle2)
        {
            pos2++;
            if (pos2 != pos) // On verifie bien que l'on n'est pas dans la même transition
            {
                if (!(strcmp(actuelle->ma_transition.etat_lu, actuelle2->ma_transition.nouvel_etat) && strcmp(actuelle->ma_transition.etat_lu, ma_machine->etat_init)))
                {
                    bool = 1; // Si l'état lu apparait dans les autres transitions en tant que nouvel état bool devient 1
                }
            }
            actuelle2 = actuelle2->suiv;
        }

        // bool = 0, on a trouvé aucune correspondance, il faut supprimer la transition
        if (!bool)
        {
            TRANSI stock = actuelle;
            actuelle = actuelle->suiv;
            if (pos == 1) // premier élément de la liste
            {
                ma_machine->liste_transitions->premier = stock->suiv;
                free(stock->ma_transition.etat_lu);
                free(stock->ma_transition.nouvel_etat);
                free(stock);
            }
            if (pos == ma_machine->nb_transitions) // dernier élément de la liste
            {
                ma_machine->liste_transitions->dernier = stock->prec;
                free(stock->ma_transition.etat_lu);
                free(stock->ma_transition.nouvel_etat);
                free(stock);
                
            }
            if ((pos != ma_machine->nb_transitions) && (pos != 1)) // au milieu de la liste
            {
                stock->prec->suiv = stock->suiv;
                stock->suiv->prec = stock->prec;
                free(stock->ma_transition.etat_lu);
                free(stock->ma_transition.nouvel_etat);
                free(stock);
            }
        }
        else
        {
            actuelle = actuelle->suiv;
        }
    }
    return 0;
}
