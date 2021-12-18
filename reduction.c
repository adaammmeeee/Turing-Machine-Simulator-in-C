#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mt.h"

/*
Pour passer d'une machine utilsant un ruban bi-infini à une machine utilisant un ruban semi-infini :
On ajoute # à l'alphabet de travail
On marque l'extremité gauche de l'entrée avec #

On effectue nos transitions normalement, si on rencontre le symbole # alors on décales toute notre bande à droite
On va donc dans un premier temps ajouter notre symbole
puis ajouter les transitions qui permettent de se décaler



*/

int bi_inf_vers_semi_inf(char *nomfic)
{
   


    MT ma_machine = init_machine(nomfic, "");
    
    FILE *newfile = NULL;
    newfile = fopen("VersionSemiInf", "w");
    fprintf( newfile,"name: %s version semi infini \n",ma_machine->nom);
    fprintf( newfile,"init:%s0\n",ma_machine->etat_init);
    fprintf( newfile,"accept:%s\n\n\n",ma_machine->etat_accepte);   
    
    TRANSI affichage = ma_machine->liste_transitions->premier;
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


    libere_machine(ma_machine);
    fclose(newfile);
    return 0;

    /*
    T transitions;

    transitions.etat_lu = malloc(10*sizeof(char));
    transitions.nouvel_etat = malloc(10*sizeof(char));


    transitions.caractere_lu = "0";
    */

    // On a toute les transitions dans la liste maintenant
}