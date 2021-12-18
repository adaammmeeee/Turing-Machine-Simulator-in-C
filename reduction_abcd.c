#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mt.h"

int abcd_vers_01(char *nomfic)
{
    MT ma_machine = init_machine(nomfic, "", "abcd_#");
    char * nouveaunom = malloc(255*sizeof(char)); // taille max d'un nom de fichier sur linux
    strcpy(nouveaunom,nomfic);
    strcat(nouveaunom, "_Vabcd");
    FILE *newfile = NULL;
    newfile = fopen(nouveaunom, "w");
    free(nouveaunom);
    fprintf(newfile, "name: %s version binaire \n", ma_machine->nom);
    fprintf(newfile, "init: %s\n", ma_machine->etat_init);
    fprintf(newfile, "accept:%s\n\n\n", ma_machine->etat_accepte);
    libere_machine(ma_machine);
    fclose(newfile);


    return 0;
}