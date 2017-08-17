/**
** \file	variable.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions de recherche de variables d'environnement.
*/

#include "minishell.h"

/**
** \brief	Recherche de variable d'environnement.
**
** \param	var -			Variable à rechercher.
** \param	environnement -	Environnement dans lequel chercher la variable.
**
** \return	Indice de la variable dans l'environnement ou -1 si celle-ci n'y
**			est pas.
*/
int	find_var(char *var, char **environnement)
{
	int	i;
	int	len;

	if (var && environnement)
	{
		i = -1;
		len = ft_strlen(var);
		while (environnement[++i])
			if (ft_strnequ(var, environnement[i], len))
				if ((environnement[i][len] && environnement[i][len] == '='))
					return (i);
	}
	return (-1);
}

/**
** \brief	Recherche de variable d'environnement.
**
** \param	var -			Variable à rechercher.
** \param	environnement -	Environnement dans lequel chercher la variable.
**
** \return	Valeur de la variable ou NULL si non trouvée.
*/
char	*get_var(char *var, char **environnement)
{
	int		i;
	char	*variable;

	variable = NULL;
	if (var && environnement)
		if ((i = find_var(var, environnement)) >= 0)
		{
			variable = environnement[i];
			if ((variable = ft_strchr(variable, '=')))
				variable++;
		}
	return (variable);
}

