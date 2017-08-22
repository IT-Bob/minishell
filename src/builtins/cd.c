/**
** \file	cd.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le builtin cd.
*/

#include "minishell.h"
#include <unistd.h>
#include <sys/stat.h>

void	freepwd(char *pwd, char *oldpwd)
{
	if (pwd)
		ft_strdel(&pwd);
	if (oldpwd)
	ft_strdel(&oldpwd);
}

static int	change_dir(char *path, char ***environnement)
{
	char		*pwd;
	char		*oldpwd;
	struct stat	buf;

	if (path && environnement)
	{
		pwd = NULL;
		if (!path[0])
			path = ".";
		if (!(oldpwd = ft_strjoin("OLDPWD=", (pwd = getcwd(NULL, 0)) ? pwd : "")))
		{
			ft_strdel(&pwd);
			return (ft_putendl_fd("1 minishell : erreur d'allocation", 2));
		}
		ft_strdel(&pwd);
		if (chdir(path))
		{
			ft_strdel(&oldpwd);
			buf.st_ino = 0;
			lstat(path, &buf);
			if ((buf.st_ino))
			{
				if (!S_ISDIR(buf.st_ino))
					return (ft_putstr_fd("cd : pas un dossier : ", 2) + ft_putendl_fd(path, 2));
				else
					return (ft_putstr_fd("cd : permission non accordée : ", 2)
						+ ft_putendl_fd(path, 2));
			}
			return (ft_putendl_fd(
				"cd : erreur de changement de dossier", 2));
		}
		alter_variable(oldpwd, environnement);
		ft_strdel(&oldpwd);
		if (!(oldpwd = ft_strjoin("PWD=", (pwd = getcwd(NULL, 0)) ? pwd : "")))
		{
			ft_strdel(&pwd);
			return (ft_putendl_fd("2 minishell : erreur d'allocation", 2));
		}
		alter_variable(oldpwd, environnement);
		ft_strdel(&pwd);
		ft_strdel(&oldpwd);
		return (0);
	}
	return (1);
}

/**
** \brief	Modification du répertoire courant.
**
** \param	argv -			Paramètres de cd.
** \param	environnement -	Environnement.
**
** \return	0 -	Exécution normale de la commande.
** \return	1 -	Erreur de modification du répertoire courant.
*/
int			cd(char **argv, char ***environnement)
{
	char	*path;
	int		ret;

	ret = 1;
	if (argv && environnement)
	{
		path = NULL;
		if (argv[0] && argv[1])
			return (ft_putendl_fd("cd : trop d'arguments", 2));
		else if ((!argv[0] || ft_strnequ(argv[0], "~", 1)) &&
				!(path = get_var("HOME", environnement[0])))
			return (ft_putendl_fd("cd : HOME non défini", 2));
		else if (ft_strequ(argv[0], "-") &&
				!(path = get_var("OLDPWD", environnement[0])))
			return (ft_putendl_fd("cd : OLDPWD non défini", 2));
		else if (!path)
			path = argv[0];
		if (argv[0] && argv[0][0] == '~')
		{
			path = ft_strjoin(path, &argv[0][1]);
			ret = change_dir(path, environnement);
			ft_strdel(&path);
		}
		else
			ret = change_dir(path, environnement);
	}
	return (ret);
}
