/**
** \file	minishell.c
** \author	Alexis Guérin
** \date	août 2017
*/

#include "minishell.h"
#include "get_next_line.h"
#include <signal.h>

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

static int	launch(char **argv, char ***environnement, int *exit)
{
	if (argv && argv[0])
	{
		if (ft_strequ(argv[0], "exit"))
			return (ft_exit(argv, exit));
		else if (ft_strequ(argv[0], "env") && environnement)
			env(&argv[1], environnement[0]);
		else if (ft_strequ(argv[0], "setenv"))
			ft_setenv(&argv[1], environnement);
		else if (ft_strequ(argv[0], "unsetenv"))
			ft_unsetenv(&argv[1], environnement);
		else if (ft_strequ(argv[0], "echo"))
			echo(&argv[1]);
		else if (ft_strequ(argv[0], "cd"))
			cd(&argv[1], environnement);
		else
			exec(argv, environnement, NULL);
	}
	return (0);
}

/**
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
	if (line)
	{
		i = -1;
		if (!(commands = ft_strsplit(line, ';')))
			ft_putendl_fd("Erreur d'allocation.", 2);
		else
			while (commands[++i] && !quit)
			{
				if (!(argv = ft_strsplit(commands[i], ' ')))
					ft_putendl_fd("Erreur d'allocation.", 2);
				quit = launch(argv, environnement, exit);
				ft_strdeldouble(argv);
			}
		ft_strdeldouble(commands);
	}
	return (quit);
}

/**
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
** 2  Ctrl-C
*/

static void	catch_signal(int signal)
{
	if (signal == 2 && !g_fils)
		ft_putstr("\n$> ");
	else if (signal == 2 && g_fils)
		ft_putendl("");
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

int			main(void)
{
	int			quit;
	int			exit;
	char		*line;
	char		**env;
	extern char	**environ;

	signal(SIGINT, catch_signal);
	line = NULL;
	quit = 0;
	exit = 0;
	if (!(env = set_new_env(environ)))
		ft_putendl_fd("minishell : Erreur de création d'environnement", 2);
	ft_putstr("$> ");
	while (!quit && !exit && get_next_line(1, &line) > 0)
	{
		!env ? env = alloc_environnement(0) : NULL;
		g_fils = 0;
		ft_striter(line, &delete_tabulation);
		if (!(quit = call_command(line, env ? &env : NULL, &exit)))
			ft_putstr("$> ");
		ft_strdel(&line);
	}
	ft_strdeldouble(env);
	ft_strdel(&line);
	return (exit);
}
