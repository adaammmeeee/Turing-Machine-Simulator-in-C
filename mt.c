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

int recupere_transition(FILE *F, int* nombre_de_ligne)
{
    int caractere = 0;
    caractere = fgetc(F);
    int retour_ligne = 0; 

    // Dans un premier temps on cherche l'état
    while (isspace(caractere))
    {
        if (caractere == '\n')
        {
            retour_ligne = 1;
            *nombre_de_ligne = *nombre_de_ligne + 1;
        }
        caractere = fgetc(F);
    }
    if (caractere == EOF) {
        printf("Fin des transitions\n");
        return 5;
    }
    if (!retour_ligne)
    {
        printf("retour à la ligne attendu à la fin de la ligne %d\n", *nombre_de_ligne);
        return 10;
    }
    if (!isupper(caractere))
    {
        printf("Lettre majuscule attendue à la ligne %d\n", *nombre_de_ligne);

        return 1;
    }
    printf("%c\n", caractere);

    //--------------------------------------

    // On cherche la virgule maintenant
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }
    if (caractere != ',')
    {
        printf("virgule attendu à la ligne %d\n", *nombre_de_ligne);
        return 2;
    }
    printf("%c\n", caractere);
    // Maintenant on cherche le caractère actuel
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }
    if (caractere != '0' && caractere != '1' && caractere != '_')
    {
        printf("0, 1 ou _ (alphabet de travail) attendu à la ligne %d\n", *nombre_de_ligne);

        return 3;
    }
    printf("%c\n", caractere);

    // Maintenant retour à la ligne et on cherche le nouvel état
    caractere = fgetc(F);
    retour_ligne = 0;
    while (isspace(caractere))
    {
        if (caractere == '\n')
        {
            retour_ligne = 1;
            *nombre_de_ligne = *nombre_de_ligne + 1;
        }
        caractere = fgetc(F);
    }

    if (!retour_ligne)
    {
         printf("retour à la ligne attendu à la fin de la ligne %d\n", *nombre_de_ligne);
        return 10;
    }

    if (!isupper(caractere))
    {
        return 1;
    }
    printf("%c\n", caractere);
    // On cherche la virgule maintenant
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }
    if (caractere != ',')
    {
        printf("virgule attendu à la ligne %d\n", *nombre_de_ligne);
        return 2;
    }
    printf("%c\n", caractere);

    // Maintenant on cherche le caractère qui remplacera
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }
    if (caractere != '0' && caractere != '1' && caractere != '_')
    {
        printf("0, 1 ou _ (alphabet de travail) attendu à la ligne %d\n", *nombre_de_ligne);
        return 3;
    }
    printf("%c\n", caractere);

    // On cherche la virgule maintenant
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }
    if (caractere != ',')
    {
        printf("virgule attendu à la ligne %d\n", *nombre_de_ligne);
        return 2;
    }
    printf("%c\n", caractere);

    // Dans quel direction on parcours la bande
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }

    if (caractere != '>' && caractere != '<' && caractere != '-')
    {
        printf(">, < ou - attendu à la ligne %d\n", *nombre_de_ligne);
        return 4;
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
    fscanf(F, "accept: %[^\n]", ma_machine.etat_accepte);
    int retour = 0;
    int nb_ligne = 3;
    retour = recupere_transition(F, &nb_ligne);
    if (retour) {
        printf("Problème lors de la lecture du fichier, Erreur n°%d\n", retour);

    }
    recupere_transition(F, &nb_ligne);
    fclose(F);

    return ma_machine;
}

void libere_machine(MT ma_machine)
{
    free(ma_machine.nom);
    free(ma_machine.etat_init);
    free(ma_machine.etat_accepte);
}