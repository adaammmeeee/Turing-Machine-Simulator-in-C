#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mt.h"

/*
Pour passer d'une machine utilsant un ruban bi-infini à une machine utilisant un ruban semi-infini :
On ajoute # à l'alphabet de travail
On marque l'extremité gauche de l'entrée avec #

On effectue nos transitions normalement, si on rencontre le symbole # alors on décale toute notre bande à droite
On va donc dans un premier temps ajouter notre symbole
puis ajouter les transitions qui permettent de se décaler
*/

// Ecrit dans un fichier (nomfic_Vabcd) la transformation d'une MT avec ruban bi infini vers ruban semi-infini
int bi_inf_vers_semi_inf(char *nomfic)
{

    MT ma_machine = init_machine(nomfic, "", "10#_");
    char *nouveaunom = malloc(255 * sizeof(char)); // taille max d'un nom de fichier sur linux
    strcpy(nouveaunom, nomfic);
    strcat(nouveaunom, "_VsemiInfini");
    FILE *newfile = NULL;
    newfile = fopen(nouveaunom, "w");
    if (newfile == NULL)
    {
        printf("Cannot open file %s\n", nouveaunom);
        return 1;
    }
    free(nouveaunom);
    fprintf(newfile, "name: %s version semi infini \n", ma_machine->nom);
    fprintf(newfile, "init: Newinit\n"); // On ajoute un nouvel état initial pour écrire le # au debut de la bande et faire le premier décalage
    fprintf(newfile, "accept:%s\n\n\n", ma_machine->etat_accepte);

    TRANSI affichage = ma_machine->liste_transitions->premier;
    printf("%c \n\n", affichage->ma_transition.caractere_lu);

    while (affichage)
    {
        fprintf(newfile, "%s,%c\n%s,%c,%c\n\n",
                affichage->ma_transition.etat_lu,
                affichage->ma_transition.caractere_lu,
                affichage->ma_transition.nouvel_etat,
                affichage->ma_transition.nouveau_caractere,
                affichage->ma_transition.direction);
        affichage = affichage->suiv;
    }

    // On place le caractère # et on décale le ruban d'un rang
    fprintf(newfile, "Newinit,1\nNewinit1,#,>\n\n");
    fprintf(newfile, "Newinit,0\nNewinit0,#,>\n\n");
    fprintf(newfile, "Newinit1,1\nNewinit1,1,>\n\n");
    fprintf(newfile, "Newinit1,0\nNewinit0,1,>\n\n");
    fprintf(newfile, "Newinit0,1\nNewinit1,0,>\n\n");
    fprintf(newfile, "Newinit0,0\nNewinit0,0,>\n\n");
    fprintf(newfile, "Newinit0,_\nGoToLeft,0,<\n\n");
    fprintf(newfile, "Newinit1,_\nGoToLeft,1,<\n\n");
    fprintf(newfile, "GoToLeft,0\nGoToLeft,0,<\n\n");
    fprintf(newfile, "GoToLeft,1\nGoToLeft,1,<\n\n");
    fprintf(newfile, "GoToLeft,#\n%s,#,>\n\n", ma_machine->etat_init);

    // Maintenant pour tous les états, si on rencontre le symbole # on décale l'entrée vers la droite puis on revient dans notre état
    for (int i = 0; i < ma_machine->nb_etats; i++)
    {
        // Quand on rencontre le symbole # et que l'on est dans l'état 'q' on va dans l'état 'q2' (décalage)
        fprintf(newfile, "%s,#\n%s2,#,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]); 

        fprintf(newfile, "%s2,0\n%s0,_,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        fprintf(newfile, "%s2,1\n%s1,_,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);


        /* Quand on est dans un état qui termine par 2 alors ça signifie que l'on commence le décalage de l'entrée vers la droite 
           Quand on est dans un état qui termine par 0 ou 1 alors on est en plein décalage
           la terminaison de l'état sert à enregistrer la lettre lu dans l'entrée pour pouvoir la replacer ensuite
        */
        fprintf(newfile, "%s0,0\n%s0,0,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        fprintf(newfile, "%s0,1\n%s1,0,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        fprintf(newfile, "%s0,_\n%s3,0,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]); 

        

        fprintf(newfile, "%s1,0\n%s0,1,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        fprintf(newfile, "%s1,1\n%s1,1,>\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        fprintf(newfile, "%s1,_\n%s3,1,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);

        // Quand un état fini par 3 le décalage est terminé, on retourne au début de la bande et on retire juste le 3 ex: q3->q

        fprintf(newfile, "%s3,1\n%s3,1,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]); // retour au début de la bande
        fprintf(newfile, "%s3,0\n%s3,0,<\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
        fprintf(newfile, "%s3,_\n%s,_,-\n\n", ma_machine->tab_etats[i], ma_machine->tab_etats[i]);
    }

    libere_machine(ma_machine);
    fclose(newfile);
    return 0;
}