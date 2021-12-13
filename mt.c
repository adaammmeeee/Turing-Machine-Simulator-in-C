#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

int recupere_transition(FILE *F)
{
    int caractere = 0;
    caractere = fgetc(F);
    
    // Dans un premier temps on cherche l'état
    while ( isspace(caractere))
    {
        caractere = fgetc(F);
    }
    if (!isupper(caractere))
    {
        return 1;
    }
    printf("%c\n", caractere);
    //--------------------------------------
    
    // On cherche la virgule maintenant
    caractere = fgetc(F);
    while (isspace(caractere))
    {
        caractere = fgetc(F);
    }
    if (caractere != ',')
    {
        return 2;
    }
    printf("%c\n", caractere);
    // Maintenant on cherche le caractère actuel
    caractere = fgetc(F);
    while (isspace(caractere))
    {
        caractere = fgetc(F);
    }
    if (caractere != '0' && caractere != '1')
    {
        return 3;
    }
    printf("%c\n", caractere);
    // Maintenant retour à la ligne
    caractere = fgetc(F);
    while (isspace(caractere))
    {
        caractere = fgetc(F);
    }
    printf("%c\n", caractere);

    if (caractere != '\n')
    {
        return 4;
    }
    caractere = fgetc(F);

    // On est bien à la ligne on cherche la prochaine majuscule
    while (caractere == '\n' || isspace(caractere))
    {
        caractere = fgetc(F);
    }
    if (!isupper(caractere))
    {
        return 1;
    }
    printf("%c\n", caractere);
    return 0;
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

    ma_machine.nom = malloc(20 * sizeof(char));
    ma_machine.etat_init = malloc(20 * sizeof(char));
    ma_machine.etat_accepte = malloc(20 * sizeof(char));

    fscanf(F, "name: %[^\n]\n", ma_machine.nom);
    fscanf(F, "init: %[^\n]\n", ma_machine.etat_init);
    fscanf(F, "accept: %[^\n]\n", ma_machine.etat_accepte);
    printf("%s\n", ma_machine.nom);
    printf("%s\n", ma_machine.etat_init);
    printf("%s\n", ma_machine.etat_accepte);

    recupere_transition(F);
    fclose(F);

    return ma_machine;
}

void libere_machine(MT ma_machine)
{
    free(ma_machine.nom);
    free(ma_machine.etat_init);
    free(ma_machine.etat_accepte);
}