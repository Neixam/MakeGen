/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 20-07-2021
 *  Modification : 20-07-2021
**/

#ifndef __STOCKDATA_H__
#define __STOCKDATA_H__

#include "Files.h"
#include <stdio.h>

typedef char **TabFlag;

typedef struct  s_data
{
    FILE    *out;
    char    *exec;
    int     opt;
    t_files files;
    TabFlag ldflags;
}               t_data;

t_data  init_data(char *exec);

int     add_ldflags(char **av, t_data *project, int ac);

void	free_data(t_data *project);

#endif
