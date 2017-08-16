/**
** \file	env.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le builtin env.
*/

#include "minishell.h"

/**
** \brief	Affiche l'environnement.
**
** \param	environnement -	Environnement à afficher.
*/
static void	print_env(char **environnement)
{
	ft_strdoubleiter(environnement,(void*)&ft_putendl);
}

/**
**
*/
static void	env_exec(char **argv, char **environnement)
{
	int	i;
	int	len;

	if (argv && environnement)
	{
		i = 0;
		len = ft_strlendouble(argv);
		while (ft_strchr(argv[i], '='))
			i++;
		ft_putnbrl(i);
		ft_putnbrl(len);
		if (i != (len - 1))
			ft_putendl("pas ok");
		else
			ft_putendl("ok");
	}
}

/**
**
*/
static void	env_i(char **argv, char *path)
{
	char	**environnement;

	if (argv && path)
	{
		if (argv[0])
		{
			environnement = NULL;
			env_exec(argv, environnement);
		}
	}
}

/**
**
*/
static void	env_u(char **argv, char **environnement, char *path)
{
	if (argv && path)
	{
		if (!argv[0])
			ft_putendl_fd("env : l'option requiert un argument -- u", 2);
		else if (environnement)
		{
			env_exec(argv, environnement);
		}
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
			env_u(&argv[1], environnement, path);
		ft_strdel(&path);
	}
}
