#include <stdio.h>
#include <stdlib.h>
#include "mt.h"

int main()
{
    //bi_inf_vers_semi_inf("test_double_semi");
    //MT ma_machine = init_machine("test_double_semi_VsemiInfini", "1001", "10_#");

    MT ma_machine = init_machine("test_abcd_binaire", "aabbdc", "abcd_#");
    abcd_vers_01("test_abcd_binaire");


    if (ma_machine == NULL)
    {
        printf("Erreur lors de l'initialisation de la machine \n");
        return 1;
    }
    calcul_pas(ma_machine, ma_machine->etat_bande->premier);
    libere_machine(ma_machine);
    return 0;
}