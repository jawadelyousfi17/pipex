/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:52:46 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 20:40:37 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	if (!s)
		return (NULL);
	t = (char *)s;
	c = (char) c;
	while (*t)
	{
		if (*t == c)
			return (t);
		t++;
	}
	if (!*t && !c)
		return (t);
	return (NULL);
}
