/**
** \file	echo.c
** \author	aguerin42@icloud.com
** \date	août 2017
**
** \brief	Fonctions pour le builtin echo().
*/

#include "minishell.h"

/**
** \brief	Affichage sur la sortie standard.
**
** Prend une chaîne de caractères en entrée et l'affiche sur la sortie standard.
**
** \param	argv -	Commande echo et la chaîne de caractères à afficher.
*/
void	echo(char **argv)
{
	if (argv && argv[1])
		ft_strdoubleiter(&argv[1], (void*)&ft_putstrs);
	ft_putchar('\n');
}
