/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:43:54 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/12 11:45:33 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	index;
	size_t	little_len;

	if (*n == 0)
		return ((char *)h);
	little_len = ft_strlen(n);
	if (len == 0)
		return (NULL);
	index = 0;
	while (*h && little_len <= len)
	{
		if (*h == *n && ft_strncmp(h, n, little_len) == 0)
			return ((char *)h);
		h++;
		len--;
	}
	return (NULL);
}
