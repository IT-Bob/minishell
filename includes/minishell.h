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

int	cd(char **argv, char ***environnement);

void	echo(char **argv);

void	env(char **argv, char **environnement);

void	ft_strdoubleiter(char **doublestr, void (*f)(char *str));

char	**copy_env(char **old_env, unsigned int len);
char	**set_new_env(char **environ);
char	**alloc_environnement(unsigned int size);
int		ft_strlendouble(char **doublestr);
int		find_var(char *var, char **environnement);
char	*get_var(char *var, char **environnement);

int		ft_exit(char **argv, int *exit);

int		ft_setenv(char **argv, char ***environnement);
int		alter_variable(char *var, char ***environnement);
int		ft_unsetenv(char **argv, char ***environnement);
int		delete_var(char ***environnement, int pos);

int		exec(char **argv, char ***environnement, char *path);

#endif

