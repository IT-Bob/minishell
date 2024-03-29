/**
** \file	env.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le builtin env.
*/

#include "minishell.h"

static int	env_exec(char **argv, char ***environnement)
{
	int	i;
	int	ret;

	i = -1;
	if (argv && environnement)
	{
		ret = 0;
		while (argv[++i] && (ft_strchr(argv[i], '=')) && !ret)
			ret = alter_variable(argv[i], environnement);
	}
	return (i);
}

static void	env_i(char **argv, char *path)
{
	int		i;
	char	**environnement;

	if (argv && argv[0])
	{
		environnement = alloc_environnement(0);
		if (environnement && ((i = env_exec(argv, &environnement)) >= 0))
		{
			if (!argv[i] || ft_strequ(argv[i], "env"))
				print_env(environnement);
			else
				exec(&argv[i], &environnement, path);
		}
		ft_strdeldouble(environnement);
	}
}

static void	env_u(char **argv, char **environ, char *path)
{
	int		i;
	char	**tmp;
	char	**env;

	if (argv && argv[0])
	{
		if (!ft_strchr(argv[0], '='))
		{
			if (!(env = copy_env(environ, ft_strlendouble(environ))))
				return ;
			if ((tmp = ft_strsplit(argv[0], '=')))
				ft_unsetenv(tmp, &env);
			if (env && ((i = env_exec(&argv[1], &env)) >= 0))
			{
				if (!argv[i + 1] || ft_strequ(argv[i + 1], "env"))
					print_env(env);
				else
					exec(&argv[i + 1], &env, path);
			}
			ft_strdeldouble(env);
			ft_strdeldouble(tmp);
		}
		else
			ft_putendl_fd("env : argument invalide", 2);
	}
}

static void	env_only(char **argv, char **environ, char *path)
{
	int		i;
	char	**environnement;

	if (argv && argv[0])
	{
		environnement = copy_env(environ, ft_strlendouble(environ));
		if (environnement && ((i = env_exec(argv, &environnement)) >= 0))
		{
			if (!argv[i] || ft_strequ(argv[i], "env"))
				print_env(environnement);
			else
				exec(&argv[i], &environnement, path);
		}
		ft_strdeldouble(environnement);
	}
}

/**
** \brief	Affichage de l'environnement
**			ou appel de fonction avec l'environnement.
**
** Sans paramètre, l'appel de env() permet d'afficher l'environnement.
** - -i permet de faire appel à un exécutable en lui envoyant un environnement
**		vide.
** - -u permet de faire appel à un exécutable en supprimant la où les variables
**		précisées.
** - Préciser une ou plusieurs variables permet de la/les modifier
**	temporairement lors de l'appel à un exécutable.
**
** \param	argv -			Paramètres de env.
** \param	environnement -	Environnement.
*/

void		env(char **argv, char **environnement)
{
	int		i;
	char	*path;

	if (argv && environnement)
	{
		if ((i = find_var("PATH", environnement)) >= 0)
		{
			if (!(path = ft_strdup(environnement[i])))
				ft_putendl_fd("minishell : erreur d'allocation", 2);
		}
		else
			path = NULL;
		if (!argv[0])
			print_env(environnement);
		else if (ft_strequ(argv[0], "-i"))
			env_i(&argv[1], path);
		else if (ft_strequ(argv[0], "-u"))
			(argv[1]) ? env_u(&argv[1], environnement, path) :
				ft_putendl_fd("env : l'option requiert un argument -- u", 2);
		else
			env_only(argv, environnement, path);
		ft_strdel(&path);
	}
}
