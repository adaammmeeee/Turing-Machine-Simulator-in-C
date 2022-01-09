#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mt.h"

int main(int argc, char **argv)
{
    /* 
    Ce programme propose plusieurs mode, en fonction du numero donné en argument
    
    "1" -> utilisé lors de l'execution normal propose à l'utilisateur un menu interactif 
           pour lui permettre de choisir le type et le nom de la MT qu'il veut executé ainsi que
           l'entrée voulu
    
    "2" -> premier make test, permet de simuler 3 machines enregistrées et les faire tourner avec l'entrée
           de l'utilisateur

    "3" -> deuxième make test, simule 2 machines, une qui a pour alphabet abcd et l'autre un ruban bi-infini

    */

    switch (atoi(argv[1]))
    {
    case 1:;
        char nomfic[256];
        printf("Entrez le nom du fichier contenant la MT \n");
        scanf("%s", nomfic);
        if (access(nomfic, F_OK))
        {
            printf("Erreur fichier non trouvé.\n");
            return 1;
        }
        printf("Entrez 1 si votre MT est simple\n");
        printf("Entrez 2 si votre MT à un alphabet qui travaille sur abcd (écrire l'entrée en binaire\n");
        printf("Entrez 3 si votre MT à un ruban bi-infini\n");
        int choix = 0;
        scanf("%d", &choix);
        printf("Veuillez entrez l'input de la MT \n");
        char input[256];
        scanf("%s", input);
        switch (choix)
        {
        case 1:;
            MT ma_machine = init_machine(nomfic, input, "01_#");
            if (ma_machine == NULL)
            {
                printf("Erreur lors de l'initialisation de la machine \n");
                return 2;
            }
            calcul_pas(ma_machine, ma_machine->etat_bande->premier);
            libere_machine(ma_machine);
            break;

        case 2:
            abcd_vers_01(nomfic);
            MT ma_machine1 = init_machine(strcat(nomfic, "_Vabcd"), input , "01_#");
            if (ma_machine1 == NULL)
            {
                printf("Erreur lors de l'initialisation de la machine \n");
                return 2;
            }
            calcul_pas(ma_machine1, ma_machine1->etat_bande->premier);
            libere_machine(ma_machine1);
            break;

        case 3:
            break;
        }

        break;

    case 2:;
        MT ma_machine = init_machine("palindrome", "10001", "01_#");
        if (ma_machine == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 1;
        }
        calcul_pas(ma_machine, ma_machine->etat_bande->premier);
        libere_machine(ma_machine);
        break;

    case 3:
        break;
    }
    /*
    //bi_inf_vers_semi_inf("test_double_semi");
    //MT ma_machine = init_machine("test_double_semi_VsemiInfini", "1001", "10_#");
    abcd_vers_01("test_abcd_binaire");

    MT ma_machine = init_machine("test_abcd_binaire_Vabcd", "1011010010", "01_#");

    if (ma_machine == NULL)
    {
        printf("Erreur lors de l'initialisation de la machine \n");
        return 1;
    }
    calcul_pas(ma_machine, ma_machine->etat_bande->premier);
    libere_machine(ma_machine);
    */
    return 0;
}