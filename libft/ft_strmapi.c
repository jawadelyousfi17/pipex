/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:41:05 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/12 13:53:37 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	size_t			s_len;
	char			*output_buffer;

	if (!s || !f)
		return (NULL);
	if (!*s)
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	index = 0;
	output_buffer = (char *)malloc((s_len + 1) * sizeof(char));
	if (!output_buffer)
		return (NULL);
	while (index < s_len)
	{
		output_buffer[index] = f(index, s[index]);
		index++;
	}
	output_buffer[index] = '\0';
	return (output_buffer);
}
