/**
** \file	minishell.c
** \author	aguerin42@icloud.com
** \date	août 2017
*/

#include "minishell.h"
#include "get_next_line.h"

#include "ft_printf.h"

/**
** \brief	Lancement de fonction.
**
** Cherche le builtin ou la fonction à appeler et la lance avec ses
** éventuels paramètres.
**
** \param argv -	Fonction et ses paramètres.
** \param old_env -	Ancien environnement où chercher l'exécutable de la fonction
**					appelée.
** \param new_env -	Nouvel environnement passé à la fonction appelée.
** \param exit -	Valeur de retour pour la fonction ft_exit(), peut être 
**					initialisée à NULL lors de l'appel.
**
** \return 0 -	Fin normale de la fonction appelée ou de sa recherche.
** \return 1 -	Quitter minishell.
*/
int			launch(char **argv, char ***old_env, char ***new_env, int *exit)
{
	if (argv && argv[0] && old_env && new_env)
	{
		if (ft_strequ(argv[0], "exit"))
			return (ft_exit(argv, exit));
		else if (ft_strequ(argv[0], "env"))
			env(new_env[0]);
		else if (ft_strequ(argv[0], "setenv"))
			ft_putendl(argv[0]);
		else if (ft_strequ(argv[0], "unsetenv"))
			ft_putendl(argv[0]);
		else if (ft_strequ(argv[0], "echo"))
			echo(argv);
		else if (ft_strequ(argv[0], "cd"))
			ft_putendl(argv[0]);
		else
			ft_printf("Lancement de %s\n", argv[0]);
	}
	return (0);
}

/*
** Sépare les différentes commandes et les lance.
** exit peut être initalisé à NULL.
*/
static int	call_command(char *line, char ***environnement, int *exit)
{
	int		i;
	int		quit;
	char	**commands;
	char	**argv;

	quit = 0;
	if (line && environnement)
	{
		i = -1;
		if (!(commands = ft_strsplit(line, ';')))
			ft_putendl_fd("Erreur d'allocation.", 2);
		else
			while (commands[++i] && !quit)
			{
				if (!(argv = ft_strsplit(commands[i], ' ')))
					ft_putendl_fd("Erreur d'allocation.", 2);
				quit = launch(argv, environnement, environnement, exit);
				ft_strdeldouble(argv);
			}
		ft_strdeldouble(commands);
	}
	return (quit);
}

/*
** Remplace les tabulations par des espaces.
*/
static void	delete_tabulation(char *str)
{
	if (str)
	{
		 if (*str == '\t')
			*str = ' ';
	}
}

/**
** \brief		Entrée du programme.
**
** minishell ne prend pas de paramètre en entrée et récupère l'environnement
** grâce à la variable externe 'environ'.\n
** Pour quitter, l'utilisateur doit utiliser la commande 'exit'.
**
** \return	0 -	Arrêt normal du programme ou autre valeur donnée par exit
**				(ft_exit()).
*/
int		main(void)
{
	int			quit;
	int			exit;
	char		*line;
	char		**environnement;
	extern char	**environ;

	line = NULL;
	quit = 0;
	exit = 0;
	if (!(environnement = set_new_env(environ)))
		ft_putendl_fd("minishell : Erreur de création d'environnement", 2);
	ft_putstr("$> ");
	while (!quit && !exit && get_next_line(1, &line) == 1)
	{
		ft_striter(line, &delete_tabulation);
		if (!(quit = call_command(line, environnement ? &environnement : NULL, &exit)))
			ft_putstr("$> ");
		ft_strdel(&line);
	}
	ft_strdeldouble(environnement);
	ft_strdel(&line);
	return (exit);
}
