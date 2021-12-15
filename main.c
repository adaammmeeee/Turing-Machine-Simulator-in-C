#include <stdio.h>
#include <stdlib.h>
#include "mt.h"

int main()
{
    BANDEAU b = malloc(sizeof(struct bandeau));
    init(b);
    MT ma_machine = init_machine("description1", "1000001");
    if (ma_machine == NULL)
    {
        printf("Erreur lors de l'initialisation de la machine \n");
        free(b);
        return 1;
    }
    affiche_bandeau(ma_machine->etat_bande);
    CARREAU tete_lecture = ma_machine->etat_bande->premier;
    calcul_pas(ma_machine, tete_lecture);
    
    libere_machine(ma_machine);
    free(b);
    return 0;
}