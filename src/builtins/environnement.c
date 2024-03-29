/**
** \file	environnement.c
** \author	aguerin42@icloud.composé
** \date	août 2017
**
** \brief	Fonction de rechercher, d'initialisation, de création
**			et de copie de l'environnement.
*/

#include "minishell.h"
#include <unistd.h>

/**
** \brief	Allocation de la mémoire pour l'environnement.
**
** \param	size -	Nombre de paramètres de l'environnement (taille).
**
** \return	L'environnement alloué ou NULL en cas d'erreur.
*/

char		**alloc_environnement(unsigned int size)
{
	char	**environnement;

	if (!(environnement = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		ft_putendl_fd("alloc_environnement : erreur d'allocation.", 2);
	return (environnement);
}

/**
** \brief	Copie d'un environnement existant.
**
** Alloue un nouvel environnement et y copie toutes les variables de l'ancien.\n
** Si la taille du nouvel environnement n'est pas suffisante, la copie n'est
** pas effectuée en entier.
**
** \param	old_env -	L'environnement à copier dans le nouveau.
** \param	len -		La taille du nouvel environnement.
**
** \return	L'environnement copié ou NULL en cas d'erreur.
*/

char		**copy_env(char **old_env, unsigned int len)
{
	int		size;
	int		i;
	char	**new_env;

	new_env = NULL;
	if (old_env)
	{
		size = ft_strlendouble(old_env);
		i = -1;
		if ((new_env = alloc_environnement(len)))
		{
			while (++i < size && i < len)
				if (!(new_env[i] = ft_strdup(old_env[i])))
				{
					ft_putendl_fd(\
							"Minishell : copy_env : erreur d'allocation", 2);
					ft_strdeldouble(new_env);
					return (NULL);
				}
		}
		else
			ft_putendl_fd("minishell : copy_env : erreur d'allocation", 2);
	}
	return (new_env);
}

/*
** Incrémente la variable SHLVL de 1 ou l'initialise à 0 si elle n'existe pas.
*/

static void	increase_shlvl(char ***environnement)
{
	int		i;
	char	*lvl;
	char	*shlvl;
	char	**tmp;

	if (environnement)
	{
		if (((i = find_var("SHLVL", environnement[0])) >= 0) &&
			(lvl = ft_strchr(environnement[0][i], '=')))
		{
			if (!(lvl = ft_itoa(ft_atoi(lvl + 1) + 1)) ||
				!(shlvl = ft_strjoin("SHLVL=", lvl)))
				ft_putendl_fd("minishell : erreur d'allocation", 2);
			ft_strdel(&lvl);
		}
		else
			shlvl = ft_strdup("SHLVL=1");
		if ((tmp = ft_strsplit(shlvl, ' ')))
			ft_setenv(tmp, environnement);
		else
			ft_putendl_fd("minishell : erreur d'allocation", 2);
		ft_strdel(&shlvl);
		ft_strdeldouble(tmp);
	}
}

/**
** \brief	Création d'un nouvel environnement.
**
** Crée un nouvel environnement composé des variables suivantes :
** - PATH
** - SHLVL
** - PWD
**
** \return	Le nouvel environnement ou NULL en cas d'erreur.
*/

static char	**create_env(void)
{
	int		size;
	char	**environnement;
	char	*pwd;

	size = 3;
	if ((environnement = alloc_environnement(size)))
	{
		if (!(environnement[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:\
/bin:/usr/sbin/:/sbin:/usr/local/munki")))
			ft_putendl_fd("minishell : create_env() : erreur d'allocation", 2);
		if (!(environnement[1] = ft_strdup("SHLVL=1")))
			ft_putendl_fd("minishell : create_env() : erreur d'allocation", 2);
		if (!(pwd = getcwd(NULL, 0)))
			ft_putendl_fd(\
			"minishell : create_env() : erreur de création de PWD", 2);
		if (!(environnement[2] = ft_strjoin("PWD=", pwd)))
			ft_putendl_fd("minishell : create_env() : erreur d'allocation", 2);
		ft_strdel(&pwd);
	}
	return (environnement);
}

/**
** \brief	Initialisation d'un nouvel environnement à partir d'un déjà existant
**			ou non.
**
** \param	environ -	L'environnement à copier dans le nouveau. Si NULL, le
**						nouveau est initialisé avec create_env().
**
** \return	Le nouvel environnement ou NULL en cas d'erreur.
*/

char		**set_new_env(char **environ)
{
	char	**environnement;

	if (environ && environ[0])
	{
		environnement = copy_env(environ, ft_strlendouble(environ));
		increase_shlvl(&environnement);
	}
	else
		environnement = create_env();
	return (environnement);
}
