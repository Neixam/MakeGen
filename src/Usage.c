/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 22-07-2021
 *  Modification : 22-07-2021
**/

#include <stdio.h>

void    usage(char *prog)
{
    printf("usage: %s [-fqh] [NAME_EXEC] [LDFLAGS]...\n", prog);
    printf("option:\n");
    printf("   -f\t\tcflags : -ansi -Wall -pedantic\n");
    printf("   -q\t\tcflags : -Wall -Wextra -Werror\n");
    printf("   -h\t\tdisplay usage\n");
}
