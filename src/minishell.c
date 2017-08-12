/**
** \file	minishell.c
** \author	aguerin42@icloud.com
** \date	août 2017
*/

#include "minishell.h"
#include "get_next_line.h"


static int	call_command(char *line, char ***environnement)
{
	int		i;
	char	**commands;
//	char	**argv;

	if (line)
	{
		if (!(commands = ft_strsplit(line, ';')))
			ft_putendl_fd("Erreur d'allocation.", 2);
		else if (environnement)
		{
			i = -1;
			while (commands[++i])
				ft_putendl(commands[i]);
		}
		ft_strdeldouble(commands);
	}
	return (0);
}

/*
** Remplace les tabulations par des espaces.
*/
static void	delete_tabulation(char **line)
{
	int		i;
	char	*tmp;

	if (line)
	{
		i = -1;
		tmp = *line;
		while (tmp[++i])
			if (tmp[i] == '\t')
				tmp[i] = ' ';
	}
}

/**
** \brief		Entrée du programme.
**
** minishell ne prend pas de paramètre en entrée et récupère l'environnement
** grâce à la variable externe 'environ'.\n
** Pour quitter, l'utilisateur doit utiliser la commande 'exit'.
**
** \return	0 -	Arrêt normal du programme.
*/
int		main(void)
{
	int			quit;
	char		*line;
	char		**environnement;
	extern char	**environ;

	line = NULL;
	if (!(environnement = set_new_env(environ)))
		ft_putendl_fd("minishell : Erreur de création d'environnement", 2);
	ft_putstr("$> ");
	quit = 0;
	while (!quit && get_next_line(1, &line) == 1 && ft_strcmp("exit", line))
	{
		delete_tabulation(&line);
		if (!(quit = call_command(line, &environnement)))
			ft_putstr("$> ");
		ft_strdel(&line);
	}
	ft_strdeldouble(environnement);
	ft_strdel(&line);
	return (quit);
}
