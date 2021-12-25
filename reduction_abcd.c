#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mt.h"

int abcd_vers_01(char *nomfic)
{
    MT ma_machine = init_machine(nomfic, "", "abcd_#");
    char *nouveaunom = malloc(255 * sizeof(char)); // taille max d'un nom de fichier sur linux
    strcpy(nouveaunom, nomfic);
    strcat(nouveaunom, "_Vabcd");
    FILE *newfile = NULL;
    newfile = fopen(nouveaunom, "w");
    free(nouveaunom);
    fprintf(newfile, "name: %s version binaire \n", ma_machine->nom);
    fprintf(newfile, "init: %s\n", ma_machine->etat_init);
    fprintf(newfile, "accept:%s\n\n\n", ma_machine->etat_accepte);
    TRANSI actuelle = ma_machine->liste_transitions->premier;

    for (int i = 0; i <= ma_machine->nb_etats; i++) // Dans un premier temps, pour chaque état on va reconnaitre la lettre
    {
        if (strcmp(ma_machine->tab_etats[i], ma_machine->etat_accepte))
        {
            fprintf(newfile, "%s,0\n%s0,0,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
            fprintf(newfile, "%s0,0\n%sA,0,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
            fprintf(newfile, "%s0,1\n%sB,1,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);

            fprintf(newfile, "%s,1\n%s1,1,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
            fprintf(newfile, "%s1,0\n%sC,0,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
            fprintf(newfile, "%s1,1\n%sD,1,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);

            fprintf(newfile, "%s,_\n%sN,_,-\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        }
    }

    while (actuelle)
    {
        char old_carac1 = '0';
        char old_carac2 = '0';

        char new_carac1 = '0';
        char new_carac2 = '0';

        switch (actuelle->ma_transition.caractere_lu)
        {
        case 'a':
            break;

        case 'b':
            old_carac2 = '1';
            break;

        case 'c':
            old_carac1 = '1';
            old_carac2 = '0';
            break;

        case 'd':
            old_carac1 = '1';
            old_carac2 = '1';
            break;

        case '_':
            old_carac1 = '_';
            old_carac2 = '_';
            break;

        default:
            exit(1);
        }

        switch (actuelle->ma_transition.nouveau_caractere)
        {
        case 'a':
            break;

        case 'b':
            new_carac2 = '1';
            break;

        case 'c':
            new_carac1 = '1';
            new_carac2 = '0';
            break;

        case 'd':
            new_carac1 = '1';
            new_carac2 = '1';
            break;

        case '_':
            new_carac1 = '_';
            new_carac2 = '_';
            break;

        default:
            exit(1);
        }

        char buffer = '0';

        (actuelle->ma_transition.caractere_lu == '_') ? (buffer = 'N') : (buffer = toupper(actuelle->ma_transition.caractere_lu));

        switch (actuelle->ma_transition.direction)
        {
        case '>':
            fprintf(newfile, "%s%c,%c\n%s%c1,%c,>\n\n",
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    old_carac1,
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    new_carac1);

            fprintf(newfile, "%s%c1,%c\n%s,%c,>\n\n",
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    old_carac2,
                    actuelle->ma_transition.nouvel_etat,
                    new_carac2);
            break;

        case '<':
            fprintf(newfile, "%s%c,%c\n%s%c1,%c,>\n\n",
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    old_carac1,
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    new_carac1);

            fprintf(newfile, "%s%c1,%c\n%sBack,%c,<\n\n",
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    old_carac2,
                    actuelle->ma_transition.nouvel_etat,
                    new_carac2);

            // On veut maintenant reculer et aller deux cases en arrière

            fprintf(newfile, "%sBack,_\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%sBack1,_,<\n", actuelle->ma_transition.nouvel_etat);

            fprintf(newfile, "%sBack,1\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%sBack1,1,<\n", actuelle->ma_transition.nouvel_etat);

            fprintf(newfile, "%sBack,0\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%sBack1,0,<\n", actuelle->ma_transition.nouvel_etat);

            // on a reculé d'une case

            fprintf(newfile, "%sBack1,_\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%sBack2,_,<\n", actuelle->ma_transition.nouvel_etat);

            fprintf(newfile, "%sBack1,1\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%sBack2,1,<\n", actuelle->ma_transition.nouvel_etat);

            fprintf(newfile, "%sBack1,0\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%sBack2,0,<\n", actuelle->ma_transition.nouvel_etat);

            // on a reculé de deux cases on va maintenant vers le nouvel état

            fprintf(newfile, "%sBack2,_\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%s,_,-\n", actuelle->ma_transition.nouvel_etat);

            fprintf(newfile, "%sBack2,1\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%s,1,-\n", actuelle->ma_transition.nouvel_etat);

            fprintf(newfile, "%sBack2,0\n", actuelle->ma_transition.nouvel_etat);
            fprintf(newfile, "%s,0,-\n", actuelle->ma_transition.nouvel_etat);

            break;

        case '-':

            fprintf(newfile, "%s%c,%c\n%s%c1,%c,>\n\n",
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    old_carac1,
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    new_carac1);

            fprintf(newfile, "%s%c1,%c\n%s,%c,<\n\n",
                    actuelle->ma_transition.etat_lu,
                    buffer,
                    old_carac2,
                    actuelle->ma_transition.nouvel_etat,
                    new_carac2);

            break;
        }

        actuelle = actuelle->suiv;
    }

    libere_machine(ma_machine);
    fclose(newfile);

    return 0;
}