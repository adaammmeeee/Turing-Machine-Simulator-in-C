#include <stdio.h>
#include <stdlib.h>
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

void ignore_commentaire(FILE *F)
{
    int a = 0;
    a = fgetc(F);
    if (a == '#')
    {
        while (fgetc(F) != '\n')
        {
        }
    }
    else
        fseek(F, -1, SEEK_SET);
}

MT init_ruban(char *nomfic, char *entree)
{
    MT ma_machine;

    FILE *F = fopen(nomfic, "r");
    if (!F)
    {
        perror("fopen");
        exit(1);
    }
    
    ma_machine.nom = malloc(20*sizeof(char));
    ma_machine.etat_init = malloc(10*sizeof(char));

    ignore_commentaire(F);
    fscanf(F, "name: %[^#\n]", ma_machine.nom);
    fscanf(F, "init:  %[^#\n]", ma_machine.etat_init);
    
    
    fclose(F);

    return ma_machine;
}


void libere_machine(MT ma_machine){
    free(ma_machine.nom);
    free(ma_machine.etat_init);
   
}