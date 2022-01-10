#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mt.h"

int main(int argc, char **argv)
{
    /* 
    Ce programme propose plusieurs modes, en fonction du numero donné en argument
    
    "1" -> Utilisé lors de l'execution normale propose à l'utilisateur un menu interactif 
           pour lui permettre de choisir le type et le nom de la MT qu'il veut executer ainsi que
           l'entré de la MT
    
    "2" -> Premier make test, permet de simuler 3 machines enregistrées et de les faire tourner avec l'entrée
           de l'utilisateur

    "3" -> Deuxième make test, simule 2 machines, une qui a pour alphabet abcd et l'autre un ruban bi-infini

    "4" -> Troisième make test, simule une machine et l'optimise

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
        printf("Entrez 1 si votre MT est dispose d'un ruban infini vers la droite\n");
        printf("Entrez 2 si votre MT a un alphabet qui travaille sur abcd (écrire l'entrée en binaire)\n");
        printf("Entrez 3 si votre MT a un ruban bi-infini\n");
        int choix = 0;
        scanf("%d", &choix);
        printf("Veuillez entrer l'input de la MT \n");
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
            MT ma_machine1 = init_machine(strcat(nomfic, "_Vbinaire"), input, "01_#");
            if (ma_machine1 == NULL)
            {
                printf("Erreur lors de l'initialisation de la machine \n");
                return 2;
            }
            calcul_pas(ma_machine1, ma_machine1->etat_bande->premier);
            libere_machine(ma_machine1);
            break;

        case 3:
            bi_inf_vers_semi_inf(nomfic);
            MT ma_machine2 = init_machine(strcat(nomfic, "_VsemiInfini"), input, "01_#");
            if (ma_machine2 == NULL)
            {
                printf("Erreur lors de l'initialisation de la machine \n");
                return 2;
            }
            calcul_pas(ma_machine2, ma_machine2->etat_bande->premier);
            libere_machine(ma_machine2);
            break;
        }

        break;

    case 2:;
        MT ma_machine3 = init_machine("palindrome", "10001", "01_#");
        if (ma_machine3 == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 1;
        }
        calcul_pas(ma_machine3, ma_machine3->etat_bande->premier);
        libere_machine(ma_machine3);

        ma_machine3 = init_machine("zero_pair", "000110", "01_#");
        if (ma_machine3 == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 1;
        }
        calcul_pas(ma_machine3, ma_machine3->etat_bande->premier);
        libere_machine(ma_machine3);

        ma_machine3 = init_machine("plus_un", "11011", "01_#");
        if (ma_machine3 == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 1;
        }
        calcul_pas(ma_machine3, ma_machine3->etat_bande->premier);
        libere_machine(ma_machine3);

        break;

    case 3:
        if (abcd_vers_01("test_abcd"))
        {
            return 2;
        }

        MT ma_machine = init_machine("test_abcd_Vbinaire", "0011011011", "01_#");

        if (ma_machine == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 1;
        }
        calcul_pas(ma_machine, ma_machine->etat_bande->premier);
        libere_machine(ma_machine);

        bi_inf_vers_semi_inf("test_bi_infini");
        ma_machine = init_machine("test_bi_infini_VsemiInfini", "000", "01_#");

        if (ma_machine == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 1;
        }

        calcul_pas(ma_machine, ma_machine->etat_bande->premier);
        libere_machine(ma_machine);
        break;

    case 4:;
        MT ma_machine4 = init_machine("opti_test", "01", "01_#");
        if (ma_machine4 == NULL)
        {
            printf("Erreur lors de l'initialisation de la machine \n");
            return 2;
        }
        printf("Avant optimisation équivalence transition: \n");
        affiche_transition(ma_machine4);
        remplace_suite_transition(ma_machine4);
        printf("Après optimisation équivalence transition: \n");
        affiche_transition(ma_machine4);

        printf("Avant optimisation code mort : \n");
        affiche_transition(ma_machine4);
        code_mort(ma_machine4);
        printf("Après optimisation code mort : \n");

        affiche_transition(ma_machine4);
        libere_machine(ma_machine4);
        break;
    }

    return 0;
}