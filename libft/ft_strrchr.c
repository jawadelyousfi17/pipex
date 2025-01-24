/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:08:29 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/11 11:11:12 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;
	char	*r;

	t = (char *)s;
	r = NULL;
	c = (char) c;
	while (*t)
	{
		if (*t == c)
			r = t;
		t++;
	}
	if (!c && !*t)
		return (t);
	return (r);
}
