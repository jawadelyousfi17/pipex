/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:21:32 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/11 13:26:07 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	index;
	size_t	s1_len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	if (!*set)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	index = 0;
	while (s1[index] && is_char_set(s1[index], set))
		index++;
	if (index == s1_len)
		return (ft_strdup(""));
	start = index;
	index = s1_len - 1;
	while (is_char_set(s1[index], set))
		index--;
	return (ft_substr(s1, start, index - start + 1));
}
