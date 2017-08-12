/**
** \file	libft.c
** \author	aguerin42@icloud.com
** \date	août 2017
**
** \brief	Fonctions à déplacer dans libft.
*/

#include "minishell.h"

/**
** \brief	Applique une fonction à chaque chaîne d'un double pointeur sur char.
**
** \param	doublestr -	Double chaîne sur laquelle appliquer la fonction.
** \param	f -			Fonction à appliquer.
*/
void			ft_strdoubleiter(char **doublestr, void (*f)(char *str))
{
	int	i;

	if (doublestr && f)
	{
		i = 0;
		while (doublestr[i])
			f(doublestr[i++]);
	}
}
