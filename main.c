#include <stdio.h>
#include <stdlib.h>
#include "mt.h"

int main()
{
    printf("Bonjour le monde\n");
    BANDEAU b = malloc(sizeof(struct bandeau));
    init(b);
    MT ma_machine = init_ruban("description", "0101011");
    libere_machine(ma_machine);
    free(b);
}