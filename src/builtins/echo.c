/**
** \file	echo.c
** \author	aguerin42@icloud.com
** \date	août 2017
*/

#include "minishell.h"

/**
** \brief Affiche sur l'entrée standard.
**
** Prend une chaîne de caractères en entrée et l'affiche sur la sortie standard.
**
** \param argv -	Chaîne de caractères à afficher.
*/
void	echo(char **argv)
{
	if (argv && argv[1])
		ft_strdoubleiter(&argv[1], (void*)&ft_putstrs);
	ft_putchar('\n');
}
