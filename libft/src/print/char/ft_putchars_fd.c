/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchars_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerin <aguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 11:26:38 by aguerin           #+#    #+#             */
/*   Updated: 2017/06/21 14:37:50 by aguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/*
** ft_putchars_fd() affiche un caractère suivi d'un espace sur le fd indiqué
** et renvoie le nombre de caractères affichés.
*/

int	ft_putchars_fd(char c, int fd)
{
	return (ft_putchar_fd(fd, c) + ft_putchar_fd(fd, ' '));
}
