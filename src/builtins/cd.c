/**
** \file	cd.c
** \author	aguerin42@icloud.com
** \date	août 2017
**
** \brief	Fonctions pour le builtin cd.
*/

#include "minishell.h"

/**
** \brief	Modification du répertoire courant.
**
** \param	argv -			Commande cd et ses paramètres.
** \param	environnement -	
**
** \return	0 -	Exécution normale de la commande.
** \return	1 -	Erreur de modification du répertoire courant.
*/
int	cd(char **argv, char ***environnement)
{
	char **environ;

	if (argv && environnement)
	{
		environ = environnement[0];
	}
}
