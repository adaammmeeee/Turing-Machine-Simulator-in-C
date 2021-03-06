#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mt.h"

// Si lettre est contenue dans le char * alphabet alors renvoie 1 sinon 0
int dans_alphabet(char *alphabet, char lettre)
{
    int bool = 0;
    for (int i = 0; i < strlen(alphabet); i++)
    {
        if (lettre == alphabet[i])
        {
            bool = 1;
        }
    }
    return bool;
}

// Gestion d'erreur vérifie que la syntaxe du fichier F est la bonne renvoie 0 si tout est bon
int test_transition(FILE *F, int *nombre_de_ligne, char *alphabet)
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
        printf("Fin de la lecture des transitions\n");
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
    while (caractere == ' ' || isdigit(caractere) || isalpha(caractere))
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
    if (!dans_alphabet(alphabet, caractere))
    {
        for (int i = 0; i < strlen(alphabet); i++)
        {
            printf("%c  ", alphabet[i]);
        }
        printf("(alphabet de travail) attendu à la ligne %d\n", *nombre_de_ligne);

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
        printf("Lettre majuscule attendue à la ligne %d\n", *nombre_de_ligne);
        return 1;
    }

    // On cherche la virgule maintenant
    caractere = fgetc(F);
    while (caractere == ' ' || isdigit(caractere) || isalpha(caractere))
    {
        caractere = fgetc(F);
    }
    if (caractere != ',')
    {
        printf("virgule attendu à la ligne %d\n", *nombre_de_ligne);
        return 2;
    }

    // Maintenant on cherche le caractère qui remplacera le caractère actuel
    caractere = fgetc(F);
    while (caractere == ' ')
    {
        caractere = fgetc(F);
    }
    if (!dans_alphabet(alphabet, caractere))
    {
        for (int i = 0; i < strlen(alphabet); i++)
        {
            printf("%c  ", alphabet[i]);
        }
        printf("(alphabet de travail) attendu à la ligne %d\n", *nombre_de_ligne);

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

// Parcourt le fichier et récupère les transition en les stockant dans la strcuture adéquate LISTE_TRANSI
LISTE_TRANSI recup_transition(FILE *F, int nb_transitions)
{
    T transition;
    LISTE_TRANSI liste_transition = malloc(sizeof(struct liste_transition));
    init_liste_transi(liste_transition);
    int caractere;
    for (int i = 0; i < nb_transitions; i++)
    {
        caractere = fgetc(F);
        transition.etat_lu = malloc(10 * sizeof(char));
        transition.nouvel_etat = malloc(10 * sizeof(char));

        while (!isupper(caractere))
        {
            caractere = fgetc(F);
        }

        int cpt = 0;
        while (isalpha(caractere) || isdigit(caractere))
        {
            transition.etat_lu[cpt] = caractere;
            caractere = fgetc(F);
            cpt++;
        }
        transition.etat_lu[cpt] = '\0';

        while (!(isdigit(caractere) || isalpha(caractere) || caractere == '_' || caractere == '#'))
        {
            caractere = fgetc(F);
        }
        transition.caractere_lu = caractere;

        caractere = fgetc(F);

        while (!isupper(caractere))
        {
            caractere = fgetc(F);
        }

        cpt = 0;
        while (isalpha(caractere) || isdigit(caractere))
        {
            transition.nouvel_etat[cpt] = caractere;
            caractere = fgetc(F);
            cpt++;
        }
        transition.nouvel_etat[cpt] = '\0';

        caractere = fgetc(F);

        while (!(isdigit(caractere) || isalpha(caractere) || caractere == '_' || caractere == '#'))
        {

            caractere = fgetc(F);
        }
        transition.nouveau_caractere = caractere;

        caractere = fgetc(F);

        while (caractere != '<' && caractere != '>' && caractere != '-')
        {
            caractere = fgetc(F);
        }
        transition.direction = caractere;
        ajout_transition(liste_transition, transition);
    }
    return liste_transition;
}

// Récupère les états à partir des transitions enregistrées dans "ma_machine"
void recup_tab_etats(MT ma_machine, int nb_transitions)
{
    char **tab_etats = malloc((nb_transitions + 1) * sizeof(char *));
    for (int i = 0; i < nb_transitions + 1; i++)
    {
        tab_etats[i] = malloc(20 * sizeof(char));
    }

    TRANSI actuelle = ma_machine->liste_transitions->premier;
    int cpt = 0;
    // On parcourt les nouveaux état, si ils ne sont pas déjà présent dans notre tableau d'état on les ajoutes
    while (actuelle)
    {
        int test = 0;
        for (int i = 0; i < cpt; i++)
        {
            if (!strcmp(actuelle->ma_transition.nouvel_etat, tab_etats[i]))
            {
                test = 1;
            }
        }
        if (!test)
        {
            strcpy(tab_etats[cpt], actuelle->ma_transition.nouvel_etat);
            cpt++;
        }
        actuelle = actuelle->suiv;
    }
    // Si l'état initiale n'est jamais un nouvel état on l'ajoute à notre tableau 
    int test = 0;
    
    for (int i = 0; i < cpt; i++)
    {
        if (!strcmp(ma_machine->etat_init, tab_etats[i]))
        {
            test = 1;
        }
    }
    if (!test)
    {
        strcpy(tab_etats[cpt], ma_machine->etat_init);
        cpt++;
    }
    printf("On a recupéré les états\n");
    ma_machine->tab_etats = tab_etats;
    ma_machine->nb_etats = cpt;
}

// Renvoie une MT initialisée à partir de son code donné dans le fichier nomfic, avec son entrée "entree" et respectant l'alphabet "alphabet"
MT init_machine(char *nomfic, char *entree, char *alphabet)
{
    MT ma_machine = malloc(sizeof(struct mt));

    FILE *F = fopen(nomfic, "r");
    if (!F)
    {
        perror("fopen");
        exit(1);
    }

    ma_machine->nom = malloc(50 * sizeof(char));
    ma_machine->etat_init = malloc(10 * sizeof(char));
    ma_machine->etat_accepte = malloc(10 * sizeof(char));
    ma_machine->etat_courant = malloc(10 * sizeof(char));

    fscanf(F, "name : %[^\n]\n", ma_machine->nom);
    fscanf(F, "init : %[^\n]\n", ma_machine->etat_init);
    fscanf(F, "accept : %[^\n]", ma_machine->etat_accepte);

    long position = ftell(F);
    rewind(F);
    // Retour en arrière pour compter le nombre de ligne du fichier et pouvoir gérer les erreurs
    int nb_ligne = 1;
    while (ftell(F) <= position)
    {
        if (fgetc(F) == '\n')
        {
            nb_ligne++;
        }
    }

    // Gestion d'erreurs
    int retour = test_transition(F, &nb_ligne, alphabet);
    int nb_transitions = 0;
    while (!retour)
    {
        nb_transitions++;
        retour = test_transition(F, &nb_ligne, alphabet);
    }
    if (retour != 5) // Si on n'a pas atteint la fin du fichier
    {
        free(ma_machine->nom);
        free(ma_machine->etat_init);
        free(ma_machine->etat_accepte);
        free(ma_machine->etat_courant);
        free(ma_machine);
        fclose(F);
        return NULL;
    }
    // Retour au début des transitions pour les enregistrer
    fseek(F, position, SEEK_SET);
    ma_machine->liste_transitions = recup_transition(F, nb_transitions);

    // affiche_transition(ma_machine);
    BANDEAU b = malloc(sizeof(struct bandeau));
    init(b);
    for (int i = 0; i < strlen(entree); i++)
    {
        ajout_elem(b, entree[i]);
    }
    ma_machine->etat_bande = b;
    strcpy(ma_machine->etat_courant, ma_machine->etat_init);
    ma_machine->position_tete_lecture = 0;
    ma_machine->nb_transitions = nb_transitions;
    recup_tab_etats(ma_machine, nb_transitions);

    fclose(F);
    return ma_machine;
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

void libere_liste_transi(LISTE_TRANSI liste_transition)
{
    while (liste_transition->premier)
    {
        TRANSI stock = liste_transition->premier;
        liste_transition->premier = liste_transition->premier->suiv;
        free(stock->ma_transition.etat_lu);
        free(stock->ma_transition.nouvel_etat);
        free(stock);
    }
    free(liste_transition->premier);
    free(liste_transition);
}

void libere_machine(MT ma_machine)
{
    for (int i = 0; i < ma_machine->nb_transitions + 1; i++)
    {
        free(ma_machine->tab_etats[i]);
    }
    free(ma_machine->tab_etats);

    free(ma_machine->nom);
    free(ma_machine->etat_init);
    free(ma_machine->etat_courant);
    free(ma_machine->etat_accepte);
    libere_liste_transi(ma_machine->liste_transitions);
    libere_bandeau(ma_machine->etat_bande);
    free(ma_machine);
}
