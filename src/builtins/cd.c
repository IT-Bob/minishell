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

static int	error_with_path(char *path, char *oldpwd)
{
	struct stat	buf;

	if (oldpwd)
		ft_strdel(&oldpwd);
	buf.st_ino = 0;
	lstat(path, &buf);
	if ((buf.st_ino))
	{
		if (!S_ISDIR(buf.st_mode))
			return (ft_putstr_fd("cd : pas un dossier : ", 2)
					+ ft_putendl_fd(path, 2));
		else
			return (ft_putstr_fd("cd : permission non accordée : ", 2)
				+ ft_putendl_fd(path, 2));
	}
	return (ft_putendl_fd("cd : erreur de changement de dossier", 2));
}

static int	error_alloc(char *str)
{
	if (str)
		ft_strdel(&str);
	return (ft_putendl_fd("minishell : erreur d'allocation", 2));
}

static int	change_dir(char *path, char ***environnement)
{
	char		*pwd;
	char		*oldpwd;

	if (path && environnement)
	{
		pwd = NULL;
		if (!path[0])
			path = ".";
		if (!(oldpwd =
					ft_strjoin("OLDPWD=", (pwd = getcwd(NULL, 0)) ? pwd : "")))
			return (error_alloc(pwd));
		ft_strdel(&pwd);
		if (chdir(path))
			return (error_with_path(path, oldpwd));
		alter_variable(oldpwd, environnement);
		ft_strdel(&oldpwd);
		pwd = getcwd(NULL, 0);
		if (!(oldpwd = ft_strjoin("PWD=", (pwd ? pwd : ""))))
			return (error_alloc(pwd));
		alter_variable(oldpwd, environnement);
		ft_strdel(&pwd);
		ft_strdel(&oldpwd);
		return (0);
	}
	return (1);
}

static int	define_path(char **argv, char **path, char ***environ)
{
	if (argv && path)
	{
		if (argv[0] && argv[1])
			return (ft_putendl_fd("cd : trop d'arguments", 2));
		else if ((!argv[0] || ft_strnequ(argv[0], "~", 1)) &&
			!(*path = ft_strdup(get_var("HOME", environ[0]))))
			return (ft_putendl_fd("cd : HOME non défini", 2));
		else if (ft_strequ(argv[0], "-")
					&& !(*path = ft_strdup(get_var("OLDPWD", environ[0]))))
			return (ft_putendl_fd("cd : OLDPWD non défini", 2));
		else if (!(*path))
			if (!(*path = ft_strdup(argv[0])))
				ft_putendl_fd("minishell : erreur d'allocation", 2);
	}
	return (0);
}

/**
** \brief	Modification du répertoire courant.
**
** \param	argv -		Paramètres de cd.
** \param	environ -	Environnement.
**
** \return	0 -	Exécution normale de la commande.
** \return	1 -	Erreur de modification du répertoire courant.
*/

int			cd(char **argv, char ***environ)
{
	char	*path;
	int		ret;

	ret = 1;
	if (argv && environ)
	{
		path = NULL;
		ret = define_path(argv, &path, environ);
		if (!ret && argv[0] && argv[0][0] == '~')
		{
			path = ft_strfreejoin(path, &argv[0][1]);
			ret = change_dir(path, environ);
		}
		else if (!ret)
		{
			if (!(ret = change_dir(path, environ)) && ft_strequ(argv[0], "-"))
				ft_putendl(path);
		}
		ft_strdel(&path);
	}
	return (ret);
}
