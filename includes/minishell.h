/**
** \file	minishell.h
** \author	aguerin42@icloud.com
** \date	août 2017
**
** \brief	Fonctions utilisées par minishell.
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

void	echo(char **argv);

void	env(char **argv, char ***old_env, char ***new_env);

void	ft_strdoubleiter(char **doublestr, void (*f)(char *str));
char	**copy_env(char **old_env, unsigned int len);
char	**create_env();
char	**set_new_env(char **environ);
char	**alloc_environnement(unsigned int size);
int		ft_strlendouble(char **doublestr);

int		ft_exit(char **argv, int *exit);

int		ft_setenv(char **argv, char ***environnement);

int		exec(char **argv, char ***old_env, char ***new_env);

#endif

