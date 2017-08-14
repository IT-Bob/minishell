/**
** \file	env.c
** \author	aguerin42@icloud.com
** \date	août 2017
**
** \brief	Fonctions pour le builtin env().
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
** \param	argv -		Commande env et ses paramètres.
** \param	old_env -	Ancien environnement.
** \param	new_env -	Nouvel environnement.
*/
void		env(char **argv, char ***old_env, char ***new_env)
{
	if (argv && old_env)
	{
		if (!new_env)
			new_env = old_env;
		if (!argv[1])
			print_env(new_env[0]);
		else if (ft_strequ(argv[1], "-i"))
			ft_putendl("env vide");
		else if (ft_strequ(argv[1], "-u"))
			ft_putendl("supp var");
	}
}
