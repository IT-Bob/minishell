#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

char	**set_new_env(char **environ);
char	**create_env();
char	**copy_env(char **old_env);

int		ft_exit(char **argv, int *exit);
void	print_env(char **environnement);

void	echo(char **argv);
void	ft_strdoubleiter(char **doublestr, void (*f)(char *str));

#endif
