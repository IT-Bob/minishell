/**
** \file	env.c
** \author	aguerin42@icloud.com
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

static void	env_exec(char **argv, char **environnement)
{
	int	i;

	if (argv && environnement)
	{
		i = 0;
		while (argv[i] && ft_strchr(argv[i], '='))
			i++;
		if (!argv[i])
			NULL;
		
	}
}

static void	env_i(char **argv)
{
	char	**environnement;

	if (argv)
	{
		if (argv[0])
		{
			environnement = NULL;
			env_exec(argv, environnement);
		}
	}
}

static void	env_u(char **argv, char **environnement)
{
	if (argv)
	{
		if (!argv[0])
			ft_putendl_fd("env : l'option requiert un argument -- u", 2);
		else if (environnement)
		{
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
** \param	argv -		Paramètres de env();
** \param	old_env -	Ancien environnement.
** \param	new_env -	Nouvel environnement.
*/
void		env(char **argv, char **environnement)
{
	if (argv && environnement)
	{
		if (!argv[0])
			print_env(environnement);
		else if (ft_strequ(argv[0], "-i"))
			env_i(&argv[1]);
		else if (ft_strequ(argv[0], "-u"))
			env_u(&argv[1], environnement);
	}
}
