/**
** \file	setenv.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le builtin setenv.
*/

#include "minishell.h"

static int	add_var(char *var, char *tmp, char **environ, char ***environnement)
{
	int		len;

	len = ft_strlendouble(environnement[0]) + 1;
	if ((environ = copy_env(environnement[0], len)))
	{
		if (!environ[len - 1] && !environ[len])
			environ[len - 1] = (tmp ? ft_strdup(var) : ft_strjoin(var, "="));
		ft_strdeldouble(environnement[0]);
		environnement[0] = environ;
	}
	else
		return (ft_putendl_fd("minishell : erreur d'allocation", 2));
	return (0);
}

/**
** \brief	Modification de la variable d'environnement indiquée.
**
** \param	var -			Variable à modifier.
** \param	environnement - Environnement.
**
** \return 0 si la modification a été effectuée avec succès
**			ou une autre valeur en cas d'erreur.
*/

int			alter_variable(char *var, char ***environnement)
{
	int		i;
	int		ret;
	char	*tmp;
	char	**environ;

	ret = 1;
	if (var && environnement)
	{
		environ = environnement[0];
		if ((tmp = ft_strchr(var, '='))
			&& !(tmp = ft_strsub(var, 0, tmp - var)))
			return (ft_putendl_fd("minishell : erreur d'allocation", 2));
		if (((i = find_var((tmp ? tmp : var), environ)) >= 0) && tmp)
		{
			ret = 0;
			ft_strdel(&environ[i]);
			if (!(environ[i] = ft_strdup(var)))
				ret = ft_putendl_fd("minishell : erreur d'allocation", 2);
		}
		else if (i < 0)
			ret = add_var(var, tmp, environ, environnement);
		ft_strdel(&tmp);
	}
	return (ret);
}

/**
** \brief	Ajout de variable(s) à l'environnement.
**
** \param	argv -			Paramètres de setenv.
** \param	environnement -	Environnement à modifier.
**
** \return	0 - Exécution normale de la commande ou une autre valeur
**				en cas d'erreur.
*/

int			ft_setenv(char **argv, char ***environnement)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	if (argv)
	{
		if (argv[0])
			while (argv[++i] && !ret)
				ret = alter_variable(argv[i], environnement);
		else
			ret = ft_putendl_fd("setenv : argument(s) nécessaire(s)", 2);
	}
	return (ret);
}
