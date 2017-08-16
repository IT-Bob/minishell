/**
** \file	unsetenv.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le builtin unsetenv.
*/

#include "minishell.h"

/*
** \brief	Message d'erreur lorsque l'utilisateur entre une variable
**			à supprimer suivie d'un '='.
**
** \param	var -	Variable donnée incorrecte.
**
** \return	1 - Fin normale de la fonction.
*/
static int incorrect_id(char *var)
{
	if (var)
	{
		ft_putstr_fd("minishell : unsetenv : ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(" : identifiant non valable", 2);
	}
	return (1);
}

/**
**	\brief	Supprime la variable donnée.
**
**	\param	environnement - Environnement.
**	\param	pos -			Position de la variable dans l'environnement.
**
** \return	0 si la suppression a été effectuée avec succès
**				ou une autre valeur en cas d'erreur.
*/
int	delete_var(char ***environnement, int pos)
{
	char	**environ;

	if (environnement && pos >= 0 && (pos < ft_strlendouble(environnement[0])))
	{
		environ = environnement[0];
		ft_strdel(&environ[pos]);
		while (environ[pos + 1])
		{
			environ[pos] = environ[pos + 1];
			pos++;
		}
		environ[pos] = NULL;
		if (!(environ = copy_env(environnement[0], ft_strlendouble(environ))))
			return (ft_putendl_fd("minishell : erreur d'allocation", 2));
		ft_strdeldouble(environnement[0]);
		environnement[0] = environ;
		return (0);
	}
	return (1);
}

/**
** \brief	Suppression de variable(s) d'environnement.
**
** \param	argv -			Paramètres de unsetenv.
** \param	environnement -	Environnement à modifier.
**
** \return	0 si la suppression a été effectuée avec succès
**				ou une autre valeur en cas d'erreur.
*/
int	ft_unsetenv(char **argv, char ***environnement)
{
	int	i;
	int	pos;
	int	ret;

	if (argv && environnement)
	{
		i = -1;
		if (environnement[0])
		{
			ret = 0;
			while (argv[++i])
				if (ft_strchr(argv[i], '='))
					ret = incorrect_id(argv[i]);
				else if ((pos = find_var(argv[i], environnement[0])) >= 0)
					delete_var(environnement, pos);
		}
		else
			ret = 1;
	}
	else if (!argv)
		return (ft_putendl_fd("unsetenv : pas assez d'arguments", 2));
	else
		ret = 1;
	return (ret);
}
