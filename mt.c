#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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

int test_transition(FILE *F, int *nombre_de_ligne)
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
    if (caractere == EOF)
    {
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

    // On cherche la virgule
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

    return 0;
}

T *recup_transition(FILE *F, int nb_transitions)
{
    T *tab_transition = malloc(nb_transitions * (sizeof(struct transition)));
    for (int i = 0; i < nb_transitions; i++)
    {
        int caractere = fgetc(F);

        while (!isupper(caractere))
        {
            caractere = fgetc(F);
        }
        tab_transition[i].etat_lu = caractere;

        caractere = fgetc(F);

        while (!(isdigit(caractere) || isalpha(caractere) || caractere == '_'))
        {
            caractere = fgetc(F);
        }
        tab_transition[i].caractere_lu = caractere;

        caractere = fgetc(F);

        while (!isupper(caractere))
        {
            caractere = fgetc(F);
        }
        tab_transition[i].nouvel_etat = caractere;

        caractere = fgetc(F);

        while (!(isdigit(caractere) || isalpha(caractere) || caractere == '_'))
        {

            caractere = fgetc(F);
        }
        tab_transition[i].nouveau_caractere = caractere;

        caractere = fgetc(F);

        while (caractere != '<' && caractere != '>' && caractere != '-')
        {
            caractere = fgetc(F);
        }
        tab_transition[i].direction = caractere;
    }
    return tab_transition;
}

void affiche_transition(T *tab_transition, int nb_transitions)
{
    for (int i = 0; i < nb_transitions; i++)
    {
        printf("%c, %c \n", tab_transition[i].etat_lu, tab_transition[i].caractere_lu);
        printf("%c, %c, %c \n", tab_transition[i].nouvel_etat, tab_transition[i].nouveau_caractere, tab_transition[i].direction);
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

MT init_machine(char *nomfic, char *entree)
{
    MT ma_machine = malloc(sizeof(struct mt));

    FILE *F = fopen(nomfic, "r");
    if (!F)
    {
        perror("fopen");
        exit(1);
    }

    ma_machine->nom = malloc(20 * sizeof(char));
    ma_machine->etat_init = malloc(20 * sizeof(char));
    ma_machine->etat_accepte = malloc(20 * sizeof(char));

    fscanf(F, "name: %[^\n]\n", ma_machine->nom);
    fscanf(F, "init: %[^\n]\n", ma_machine->etat_init);
    fscanf(F, "accept: %[^\n]", ma_machine->etat_accepte);
    long position = ftell(F);
    rewind(F);
    int nb_ligne = 1;
    while (ftell(F) <= position)
    {
        if (fgetc(F) == '\n')
        {
            nb_ligne++;
        }
    }

    int retour = test_transition(F, &nb_ligne);
    int nb_transitions = 0;
    while (!retour)
    {
        nb_transitions++;
        retour = test_transition(F, &nb_ligne);
    }
    if (retour != 5) // Si on n'a pas atteint la fin du fichier
    {
        free(ma_machine->nom);
        free(ma_machine->etat_init);
        free(ma_machine->etat_accepte);
        free(ma_machine);
        fclose(F);
        return NULL;
    }
    fseek(F, position - 1, SEEK_SET);
    ma_machine->tab_transitions = recup_transition(F, nb_transitions);
    BANDEAU b = malloc(sizeof(struct bandeau));
    init(b);
    for (int i = 0; i < strlen(entree); i++)
    {
        ajout_elem(b, entree[i]);
    }
    ma_machine->etat_bande = b;
    ma_machine->etat_courant = ma_machine->etat_init[0];
    printf("Etat courant : %c\n", ma_machine->etat_courant);
    ma_machine->position_tete_lecture = 0;
    ma_machine->nb_transitions = nb_transitions;
    affiche_transition(ma_machine->tab_transitions, nb_transitions);
    fclose(F);
    return ma_machine;
}

int calcul_pas(MT ma_machine, CARREAU tete_lecture)
{

    int j = 0;
    int cpt = 0;
    for (int i = 0; i < ma_machine->nb_transitions; i++)
    {
        // printf("%c   %c \n", ma_machine->tab_transitions[i].etat_lu, ma_machine->tab_transitions[i].caractere_lu);
        if ((ma_machine->tab_transitions[i].etat_lu == ma_machine->etat_courant) && (ma_machine->tab_transitions[i].caractere_lu == tete_lecture->valeur))
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
        ma_machine->etat_courant = ma_machine->tab_transitions[j].nouvel_etat;
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
        printf("Premier pas \n");
        affiche_bandeau(ma_machine->etat_bande);
        printf("Position de la tête de lecture : %d\n", ma_machine->position_tete_lecture + 1);
        printf("Etat courant : %c\n", ma_machine->etat_courant);

        return calcul_pas(ma_machine, tete_lecture);
    }

    if (cpt == 0)
    {
        if (ma_machine->etat_courant == ma_machine->etat_accepte[0])
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

void libere_bandeau(BANDEAU b)
{
    while (b->premier)
    {
        CARREAU stock = b->premier;
        b->premier = b->premier->suiv;
        free(stock);
    }
    free(b->premier);
    free(b);
}

void libere_machine(MT ma_machine)
{
    free(ma_machine->nom);
    free(ma_machine->etat_init);
    free(ma_machine->etat_accepte);
    free(ma_machine->tab_transitions);
    libere_bandeau(ma_machine->etat_bande);
    free(ma_machine);
}