/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 21-07-2021
 *  Modification : 21-07-2021
**/

#ifndef __FILES_H__
#define __FILES_H__

typedef char **TabDep;

typedef struct  s_file
{
    char            *name;
    TabDep          dependencies;
    struct s_file   *next;
}               t_file,
                *t_files;

t_files new_file(char *name);

int     add_files(t_files *files, char *name);

int     add_dependencies(t_files *files, char dependencies[][256], int n);

void    free_files(t_files *files);

#endif
