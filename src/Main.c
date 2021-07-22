/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 20-07-2021
 *  Modification : 20-07-2021
**/

#include "StockData.h"
#include "Process.h"
#include <unistd.h>
#include <getopt.h>

int     main(int ac, char **av)
{
    const char  *optstring = "fq";
    int         ret;
    int         opt = 0;
    t_data      project;

    while ((ret = getopt(ac, av, optstring)) != EOF)
    {
        switch (ret)
        {
            case 'f':
                opt = 1;
                break;
            case 'q':
                opt = 0;
                break;
            case '?':
                printf("unknown option %c\n", optopt);
                break;
            default :
                printf("default : unknown option %c\n", optopt);
                break;
        }
    }
    project = (ac - optind == 0) ? init_data("a.out") : init_data(av[optind]);
    project.opt = opt;
    if (add_ldflags(&av[optind + 1], &project, ac - (optind + 1)))
        return (1);
    if (repo_parsing(&project))
        return (1);
    make_write(project);
    free_data(&project);
    return (0);
}
