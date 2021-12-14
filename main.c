#include <stdio.h>
#include <stdlib.h>
#include "mt.h"

int main()
{
    BANDEAU b = malloc(sizeof(struct bandeau));
    init(b);
    MT ma_machine = init_ruban("description", "0101011");
    if (ma_machine == NULL) {
        printf("Erreur lors de l'initialisation de la machine \n");
        return 1;
    }
    libere_machine(ma_machine);
    free(b);
    return 0;
}