/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:34:28 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/12 11:45:02 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		size;
	size_t		index;
	char		*new_s;

	size = ft_strlen(s);
	new_s = (char *)malloc((sizeof(char) * (size + 1)));
	if (!new_s)
		return (NULL);
	index = 0;
	while (index < size)
	{
		new_s[index] = s[index];
		index++;
	}
	new_s[index] = '\0';
	return (new_s);
}
