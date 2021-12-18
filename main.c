#include <stdio.h>
#include <stdlib.h>
#include "mt.h"

int main()
{
    BANDEAU b = malloc(sizeof(struct bandeau));
    init(b);
    bi_inf_vers_semi_inf("description");
    MT ma_machine = init_machine("VersionSemiInf", "100");
    if (ma_machine == NULL)
    {
        printf("Erreur lors de l'initialisation de la machine \n");
        free(b);
        return 1;
    }
    calcul_pas(ma_machine, ma_machine->etat_bande->premier);
    libere_machine(ma_machine);
    free(b);
    return 0;
}