/**
 *  Auteur       : Bourennane Amine
 *  Creation     : 21-07-2021
 *  Modification : 21-07-2021
**/

#include <stdlib.h>
#include <string.h>

int    ft_strlen(char *s)
{
    int     ret;

    for (ret = 0; *s; ret++, s++);
    return (ret);
} 

char    *ft_strdup(char *s)
{
    char    *ret;
    int     i;

    if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
        return (NULL);
    for (i = 0; s[i]; i++)
        ret[i] = s[i];
    ret[i] = 0;
    return (ret);
}
