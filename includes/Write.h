/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 20-07-2021
 *  Modification : 20-07-2021
**/

#ifndef __WRITE_H__
#define __WRITE_H__

#include <stdio.h>
#include "Files.h"

void    start_write(FILE *out);

void    exec_write(char *exec, FILE *out);

void	cflags_write(int opt, FILE *out);

void	ldflags_write(char **ldflags, FILE *out);

void	src_write(t_files files, FILE *out);

void    obj_write(FILE *out);

void    start_compil_write(FILE * out);

void    dependencies_write(t_files files, FILE *out);

void    end_compil_write(FILE *out);

void    end_write(FILE *out);

#endif
