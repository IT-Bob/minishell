/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerin <aguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:22:14 by aguerin           #+#    #+#             */
/*   Updated: 2016/11/17 10:46:38 by aguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	lenofb;
	unsigned int	lenofl;
	char			*big1;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char*)big);
	lenofb = ft_strlen(big);
	lenofl = ft_strlen(little);
	big1 = (char*)big;
	if (len != 0)
	{
		while ((i + lenofl <= len) && (i + lenofl <= lenofb))
		{
			if (!ft_strncmp(little, &big1[i], ft_strlen(little)))
				return (&big1[i]);
			i++;
		}
	}
	return (NULL);
}
