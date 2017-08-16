/**
** \file	exit.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonction pour le builtin exit.
*/

#include "minishell.h"

/**
** \brief	Quitter Minishell.
**
** \param	argv -	Commande exit et ses paramètres.
** \param	exit -	Valeur à renvoyer au moment de quitter le programme.
**
** \return	1 - Valeur pour indiquer à la fonction principale de quitter.
*/
int			ft_exit(char **argv, int *exit)
{
	if (argv && exit)
	{
		*exit = 0;
		if (argv[1])
		{
			*exit = ft_atoi(argv[1]);
			if (ft_strlen(argv[1]) != ft_nbrlen(*exit))
			{
				ft_putstr_fd("Minishell : exit : Nombre incorrect : ", 2);
				ft_putendl_fd(argv[1], 2);
				*exit = 1;
			}
		}
	}
	return (1);
}

