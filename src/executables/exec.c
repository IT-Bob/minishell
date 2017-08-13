/**
** \file	exec.c
** \author	Alexis Guérin
** \date	août 2017
**
** \brief	Fonctions pour le lancement d'exécutables.
*/

#include "minishell.h"

/**
** \brief	Lancement d'exécutables.
**
** exec() cherche l'exécutable donné dans argv à l'aide de la variable PATH.
** new_env est donnée comme environnement au lancement de l'exécutable.
**
** \param	argv -		Fonction et ses paramètres.
** \param	old_env -	Ancien environnement où chercher les chemins
**						des exécutables grâce au PATH.
** \param	new_env -	Nouvel environnement passé à l'exécutable.
**						Peut être identique à old_env.
**						Si NULL, old_env est utilisé à la place.
**
** \return	0 -	L'exécutable a pu être trouvé et lancé.
** \return	1 -	L'exécutable n'a pu être trouvé ou lancé.
*/
int	exec(char **argv, char ***old_env, char ***new_env)
{
	ft_putendl("EXEC");
	if (argv && old_env)
	{
		if (!new_env)
			new_env = old_env;
	}
	return (1);
}

