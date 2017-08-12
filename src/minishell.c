/**
** \file	minishell.c
** \author	aguerin42@icloud.com
** \date	août 2017
*/

#include "minishell.h"
#include "get_next_line.h"

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
	char		*line;
	char		**environnement;
	extern char	**environ;

	line = NULL;
	if (!(environnement = set_new_env(environ)))
		ft_putendl_fd("minishell : Erreur de création d'environnement", 2);
	ft_putstr("$> ");
	while (get_next_line(1, &line) == 1 && ft_strcmp("exit", line))
	{
		ft_putendl(line);
		ft_strdel(&line);
		ft_putstr("$> ");
	}
	ft_strdeldouble(environnement);
	ft_strdel(&line);
	return (0);
}
