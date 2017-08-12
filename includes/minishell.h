#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

char	**set_new_env(char **environ);
char	**create_env();
char	**copy_env(char **old_env);

#endif
