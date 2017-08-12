/**
** \file	env.c
** \author	aguerin42@icloud.com
** \date	août 2017
*/

#include "minishell.h"
#include <unistd.h>

/**
** \brief	Affiche de l'environnement.
**
** \param	environnement -	Environnement à afficher.
*/
void			print_env(char **environnement)
{
	ft_strdoubleiter(environnement,(void*)&ft_putendl);
}

/**
** \brief	Calcul la longueur de la première dimension d'un double pointeur
**			sur char.
**
** \param	doublestr -	Double pointeur sur char.
**
** \return	Longueur de la première dimension.
*/
static int		ft_strlendouble(char **doublestr)
{
	int	i;

	i = 0;
	if (doublestr)
		while (doublestr[i])
			i++;
	return (i);
}

/*
** \brief	Allocation de la mémoire pour l'environnement.
**
** \param	size -	Nombre de paramètres de l'environnement (taille).
**
** \return	L'environnement alloué ou NULL en cas d'erreur.
*/
static char	**alloc_environnement(unsigned int size)
{
	char	**environnement;

	if (!(environnement = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		ft_putendl_fd("alloc_environnement : Erreur d'allocation.", 2);
	return (environnement);
}

/**
** \brief	Copie d'un environnement existant.
**
** Alloue un nouvel environnement et y copie toutes les variables de l'ancien.
**
** \param	old_env -	L'environnement à copier dans le nouveau.
**
** \return	L'environnement copié ou NULL en cas d'erreur.
*/

char	**copy_env(char **old_env)
{
	char	**environnement;
	int		size;
	int		i;

	environnement = NULL;
	if (old_env)
	{
		size = ft_strlendouble(old_env);
		i = -1;
		if ((environnement = alloc_environnement(size)))
			while (++i < size)
				if (!(environnement[i] = ft_strdup(old_env[i])))
				{
					ft_putendl_fd("copy_env : Erreur d'allocation", 2);
					ft_strlendouble(environnement);
					return (NULL);
				}
	}
	return (environnement);
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
char	**create_env()
{
	int		size;
	char	**environnement;
	char	*pwd;

	size = 3;
	if ((environnement = alloc_environnement(size)))
	{
		if (!(environnement[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:\
/bin:/usr/sbin/:/sbin:/usr/local/munki")))
			ft_putendl_fd("create_env() : Erreur d'all!ocation", 2);
		if (!(environnement[1] = ft_strdup("SHLVL=1")))
			ft_putendl_fd("create_env() : Erreur d'allocation", 2);
		if (!(pwd = getcwd(NULL, 0)))
			ft_putendl_fd("create_env() : Erreur de création de PWD", 2);
		if (!(environnement[2] = ft_strjoin("PWD=", pwd)))
			ft_putendl_fd("create_env() : Erreur d'allocation", 2);
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
char	**set_new_env(char **environ)
{
	char	**environnement;

	if (environ && environ[0])
		environnement = copy_env(environ);
	else
		environnement = create_env();
	return (environnement);
}

