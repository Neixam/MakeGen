/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 20-07-2021
 *  Modification : 20-07-2021
**/

#define _DEFAULT_SOURCE
#include "Process.h"
#include "Files.h"
#include "Write.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PATH_SIZE 256
#define BUF_SIZE 256
#define DEP_SIZE 32

int     match(char *s1, char *s2)
{
    if (*s1 == '*' && *s2)
        return (match(s1, s2 + 1) || match(s1 + 1, s2 + 1));
    if (*s2 == '*' && *s1)
        return (match(s1 + 1, s2) || match(s1 + 1, s2 + 1));
    if (*s1 == '\0' || *s2 == '\0')
    {
        if (*s1 == *s2)
            return (1);
        return (0);
    }
    if (*s1 == *s2)
        return (match(s1 + 1, s2 + 1));
    return (0);
    
}

int     filter(const struct dirent *f)
{
    return ((DT_DIR & f->d_type && strcmp(".", f->d_name)
            && strcmp("..", f->d_name))
            || match("*.c", (char*)f->d_name));
}

void    recup_inc_name(char *dest, char *src)
{
    int     i;

    for (; *src; src++)
    {
        if (*src == '\"')
            for (i = 0, src++; *src != '\"' && *src; src++, i++)
                dest[i] = *src;
    }
    dest[i] = 0;
}

int     recup_dependencies(t_files *files, char *path)
{
    FILE    *f;
    char    buf[BUF_SIZE];
    char    dep[DEP_SIZE][BUF_SIZE];
    int     size;

    if (!(f = fopen(path, "r")))
    {
        perror("recup_dependencies");
        return (1);
    }
    for (size = 0; fgets(buf, BUF_SIZE, f);)
    {
        if (match("#include \"*\"\n", buf))
        {
            recup_inc_name(dep[size], buf);
            size++;
        }
    }
    if (add_dependencies(files, dep, size))
        return (1);
    fclose(f);
    return (0);
}

int     recup_files(t_data *project, char *path)
{
    struct dirent   **files;
    char            path2[PATH_SIZE];
    int             nb_file;
    int             i;

    if ((nb_file = scandir(path, &files, filter, alphasort)) == -1)
    {
        perror("recup_files");
        return (1);
    }
    for (i = 0; i < nb_file; i++)
    {
        snprintf(path2, PATH_SIZE, "%s%s", path, files[i]->d_name);
        if (!(DT_DIR & files[i]->d_type))
        {
            files[i]->d_name[strlen(files[i]->d_name) - 2] = 0;
            if (add_files(&(project->files), files[i]->d_name))
                return (1);
            if (recup_dependencies(&(project->files), path2))
                return (1);
        }
        else
        {
            snprintf(path2, PATH_SIZE, "%s/", path2);
            if (recup_files(project, path2))
                return (1);
        }
        free(files[i]);
    }
    free(files);
    return (0);
}

int     repo_parsing(t_data *project)
{
    char    path[PATH_SIZE];

    snprintf(path, PATH_SIZE, "src/");
    if (recup_files(project, path))
        return (1);
    return (0);
}

void    make_write(t_data project)
{
    start_write(project.out);
    exec_write(project.exec, project.out);
    cflags_write(project.opt, project.out);
    ldflags_write(project.ldflags, project.out);
    src_write(project.files, project.out);
    obj_write(project.out);
    start_compil_write(project.out);
    dependencies_write(project.files, project.out);
    end_compil_write(project.out);
    end_write(project.out);
}
