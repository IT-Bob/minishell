/**
** \file	exec.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le lancement d'exécutables.
*/

#include "minishell.h"
#include "ft_printf.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
** \brief	Recherche de variable d'environnement.
**
** \param	Variable à rechercher.
** \param	Environnement dans lequel chercher la variable.
**
** \return	Indice de la variable dans l'environnement ou -1 si celle-ci n'y
**			est pas.
*/
static int	find_var(char *var, char **environnement)
{
	int	i;
	int	len;

	if (var && environnement)
	{
		i = -1;
		len = ft_strlen(var);
		while (environnement[++i])
			if (ft_strnequ(var, environnement[i], len))
				if ((environnement[i][len] && environnement[i][len] == '='))
					return (i);
	}
	return (-1);
}

/*
** Cherche l'exécutable dans le PATH de l'environnement.
*/
static int	search_exec(char **argv, char ***old_env, char ***new_env)
{
	int		i;
	char	*tmp;
	char	*cut;
	char	*path;

	if (argv && old_env && new_env)
	{
		i = find_var("PATH", old_env[0]);
		path = ((i >= 0) ? old_env[0][i] : NULL);
		if (path && (tmp = ft_strchr(path, '=')))
			path = tmp + 1;
		tmp = NULL;
		if (path)
		{
			cut = ft_strchr(path, ':');
			tmp = (cut ? ft_strsub(path, 0, cut - path) : path);
			ft_putendl(tmp);
			return (0);
		}
		else
			return (ft_printf("minishell : Commande inconnue : %s\n", argv[0]));
	}
	return (1);
}

/**
** \brief	Lancement d'exécutables.
**
** exec() cherche l'exécutable donné dans argv à l'aide de la variable PATH.
** new_env est donnée comme environnement au lancement de l'exécutable.
**
** \param	argv -		Fonction et ses paramètres.
** \param	old_env -	Ancien environnement où chercher les chemins
**						des exécutables grâce au PATH.
** \param	new_env -	Nouvel environnement passé à l'exécutable.
**						Peut être identique à old_env.
**						Si NULL, old_env est utilisé à la place.
**
** \return	0 -	L'exécutable a pu être trouvé et lancé.
** \return	1 -	L'exécutable n'a pu être trouvé ou lancé.
*/
int	exec(char **argv, char ***old_env, char ***new_env)
{
	pid_t	f;

	if (argv && argv[0] && old_env)
	{
		if (!new_env)
			new_env = old_env;
		if ((f = fork()))
			wait(NULL);
		else
		{
			if (argv[0][0] && (argv[0][0] == '/' || ft_strnequ(argv[0], "./", 2)))
				execve(argv[0], argv, new_env[0]);
			else
				return (search_exec(argv, old_env, new_env));
		}
	}
	return (1);
}

