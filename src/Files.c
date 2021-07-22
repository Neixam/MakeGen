/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 21-07-2021
 *  Modification : 21-07-2021
**/

#include "Files.h"
#include "BasicFt.h"
#include <stdio.h>
#include <stdlib.h>

t_files new_file(char *name)
{
    t_files ret;

    if (!(ret = (t_files)malloc(sizeof(t_file))))
        return (NULL);
    if (!(ret->name = ft_strdup(name)))
    {
        perror("new_file");
        exit(1);
    }
    ret->dependencies = NULL;
    ret->next = NULL;
    return (ret);
}

int     add_files(t_files *files, char *name)
{
    t_files tmp;

    tmp = *files;
    if (!(*files = new_file(name)))
        return (1);
    (*files)->next = tmp;
    return (0);
}

int     add_dependencies(t_files *files, char dependencies[][256], int n)
{
    int     i;

    if (!((*files)->dependencies = (TabDep)malloc(sizeof(char*) * (n + 1))))
        return (1);
    for (i = 0; i < n; i++)
    {
        if (!((*files)->dependencies[i] = ft_strdup(dependencies[i])))
            return (1);
    }
    (*files)->dependencies[i] = NULL;
    return (0);
}

void    free_files(t_files *files)
{
    int     i;

    if (!*files)
        return ;
    free_files(&(*files)->next);
    for (i = 0; (*files)->dependencies[i] != NULL; i++)
        free((*files)->dependencies[i]);
    free((*files)->name);
    free((*files)->dependencies);
    free(*files);
}
