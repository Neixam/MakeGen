# MakeGen

### What this ?

__*MakeGen*__ is a generator of Makefile in language **C** which be careful about the dependencies.

### Install

You just may to use the command **make** in the root of repo.

### Usage

- usage:

   ./MakeGen [-fqh] [NAME_EXEC] [LDFLAGS]...
   
   NAME_EXEC is the name of your executable.
   
   LDFLAGS are all the loading library flags that you need.
   
- option:

   - -f       cflags : -ansi -Wall -pedantic

   - -q       cflags : -Wall -Wextra -Werror

   - -h		    display usage
