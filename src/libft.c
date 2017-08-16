/**
** \file	libft.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions à déplacer dans libft.
*/

#include "minishell.h"

/**
** \brief	Calcul la longueur de la première dimension d'un double pointeur
**			sur char.
**
** \param	doublestr -	Double pointeur sur char.
**
** \return	Longueur de la première dimension.
*/
int		ft_strlendouble(char **doublestr)
{
	int	i;

	i = 0;
	if (doublestr)
		while (doublestr[i])
			i++;
	return (i);
}

/**
** \brief	Applique une fonction à chaque chaîne d'un double pointeur sur char.
**
** \param	doublestr -	Double chaîne sur laquelle appliquer la fonction.
** \param	f -			Fonction à appliquer.
*/
void	ft_strdoubleiter(char **doublestr, void (*f)(char *str))
{
	int	i;

	if (doublestr && f)
	{
		i = 0;
		while (doublestr[i])
			f(doublestr[i++]);
	}
}
