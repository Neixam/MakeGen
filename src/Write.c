/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 20-07-2021
 *  Modification : 20-07-2021
**/

#include "Write.h"
#include "Files.h"
#include <stdio.h>

void    start_write(FILE *out)
{
    fprintf(out, "# Variable\n");
    fprintf(out, "purple = \\033[0;35m\n");
    fprintf(out, "cyan = \\033[0;36m\n");
    fprintf(out, "green = \\033[0;32m\n");
    fprintf(out, "neutral = \\033[0m\n");
    fprintf(out, "red = \\033[31m\n");
    fprintf(out, "\nINC_PATH = includes/\n");
    fprintf(out, "CC = gcc\n");
}

void    exec_write(char *exec, FILE *out)
{
    fprintf(out, "EXEC = %s\n", exec);
}

void    cflags_write(int opt, FILE *out)
{
    fprintf(out, "CFLAGS = ");
    if (opt)
        fprintf(out, "-ansi -pedantic -Wall\n");
    else
        fprintf(out, "-Wall -Wextra -Werror\n");
}

void    ldflags_write(char **ldflags, FILE *out)
{
    int     i;

    if (!*ldflags)
        return ;
    fprintf(out, "LDFLAGS = ");
    for (i = 0; ldflags[i] != NULL; i++)
        fprintf(out, "-%s ", ldflags[i]);
    fprintf(out, "\n");
}

void    src_write(t_files files, FILE *out)
{
    if (!files)
        return ;
    fprintf(out, "SRC\t=\t%s.c \\\n", files->name);
    for (files = files->next; files; files = files->next)
        fprintf(out, "\t\t%s.c \\\n", files->name);
    fprintf(out, "\nSRC_PATH = $(shell find src -type d)\n");
    fprintf(out, "vpath %%.c $(foreach rep, $(SRC_PATH), $(rep))\n");
}

void    obj_write(FILE *out)
{
    fprintf(out, "OBJ_PATH = obj/\n");
    fprintf(out, "OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))\n");
}

void    start_compil_write(FILE * out)
{
    fprintf(out, "\n# Compilation\n");
    fprintf(out, "$(EXEC) : $(OBJ)\n");
    fprintf(out, "\t$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)\n\n");
}

void    dependencies_write(t_files files, FILE *out)
{
    int     i;

    for (; files; files = files->next)
    {
        if (!files->dependencies[0])
            continue;
        fprintf(out, "$(OBJ_PATH)%s.o : ", files->name);
        for (i = 0; files->dependencies[i] != NULL; i++)
            fprintf(out, "$(INC_PATH)%s ", files->dependencies[i]);
        fprintf(out, "\n\n");
    }
}

void    end_compil_write(FILE *out)
{
    fprintf(out, "$(OBJ_PATH)%%.o : %%.c\n");
    fprintf(out, "\t@mkdir -p $(OBJ_PATH)\n");
    fprintf(out, "\t$(CC) -o $@ -c $< $(CFLAGS) -I $(INC_PATH)\n\n");
}

void    end_write(FILE *out)
{
    fprintf(out, "# Rules\n");
    fprintf(out, "all : $(EXEC)\n\n");
    fprintf(out, "clean :\n");
    fprintf(out, "\t@echo \"${red}Deleted objects ...${neutral}\"\n");
    fprintf(out, "\t@/bin/rm -rf $(OBJ_PATH)\n");
    fprintf(out, "\t@echo \"${green}END${neutral}\"\n\n");
    fprintf(out, "fclean : clean\n");
    fprintf(out, "\t@echo \"${red}Uninstall project ...${neutral}\"\n");
    fprintf(out, "\t@/bin/rm -rf $(EXEC)\n");
    fprintf(out, "\t@echo \"${green}END${neutral}\"\n\n");
    fprintf(out, "re : fclean all\n\n");
    fprintf(out, ".PHONY : all clean fclean re");
}
