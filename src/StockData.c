/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 20-07-2021
 *  Modification : 20-07-2021
**/

#include "StockData.h"
#include "BasicFt.h"
#include <stdio.h>
#include <stdlib.h>

t_data  init_data(char *exec)
{
    t_data  ret;

    if (!(ret.out = fopen("Makefile", "w")))
    {
        perror("init_data");
        exit(2);
    }
    if (!(ret.exec = ft_strdup(exec)))
    {
        perror("init_data");
        exit(1);
    }
    ret.files = NULL;
    ret.ldflags = NULL;
    return (ret);
}

int     add_ldflags(char **av, t_data *project, int ac)
{
    int     i;

    if (!(project->ldflags = (char**)malloc(sizeof(char*) * (ac + 1))))
        return (1);
    for (i = 0; i < ac; i++)
        if (!(project->ldflags[i] = ft_strdup(av[i])))
            return (1);
    project->ldflags[i] = NULL;
    return (0);
}

void	free_data(t_data *project)
{
	int		i;

	fclose(project->out);
	free(project->exec);
	free_files(&project->files);
	for (i = 0; project->ldflags[i]; i++)
		free(project->ldflags[i]);
	free(project->ldflags);
}
