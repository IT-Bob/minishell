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

static char	*add_slash(char *path)
{
	int		len;
	char	*tmp;

	if (path)
	{
		len = ft_strlen(path);
		if (path[len - 1] != '/')
		{
			if (!(tmp = ft_strjoin(path, "/")))
				ft_putendl_fd("minishell : erreur d'allocatin", 2);
			else
			{
				ft_strdel(&path);
				path = tmp;
			}
		}
	}
	return (path);
}

static char	*cut_path(char *path)
{
	char	*tmp;

	if (path)
	{
		tmp = ft_strchr(path, ':');
		if (tmp)
			tmp = ft_strsub(path, 0, tmp - path);
		else
			tmp = ft_strsub(path, 0, ft_strlen(path));
		return (add_slash(tmp));
	}
	return (NULL);
}

/*
** Cherche l'exécutable dans le PATH de l'environnement.
*/
static int	search_exec(char **argv, char ***environnement, char *old_path)
{
	int		i;
	char	*tmp;
	char	*path;

	if (argv && environnement)
	{
		if (!old_path)
		{
			i = find_var("PATH", environnement[0]);
			path = ((i >= 0) ? environnement[0][i] : NULL);
		}
		else
			path = old_path;
		if (path && (path = ft_strchr(path, '=')))
			path = path + 1;
		if (path)
		{
			while ((tmp = cut_path(path)))
			{
				tmp = ft_strfreejoin(tmp, argv[0]);
				execve(tmp, argv, environnement[0]);
				ft_strdel(&tmp);
				if ((path = ft_strchr(path, ':')))
					path = path + 1;
			}
		}
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
** \return	0 si l'exécutable a pu être trouvé et lancé
**				ou une autre valeur sinon.
*/
int	exec(char **argv, char ***environnement, char *path)
{
	int		ret;
	pid_t	f;

	if (argv && argv[0] && environnement)
	{
		if ((f = fork()))
			wait(NULL);
		else
		{
			if (argv[0][0] && (argv[0][0] == '/' || ft_strnequ(argv[0], "./", 2)))
				ret = execve(argv[0], argv, environnement[0]);
			else
				ret = search_exec(argv, environnement, path);
			if (ret)
			{
				ft_putstr_fd("Minishell : Commande introuvable : ", 2);
				ft_putendl_fd(argv[0], 2);
			}
			exit(0);
		}
	}
	return (0);
}

