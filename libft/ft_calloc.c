/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:31:09 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/13 09:18:44 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	index;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb && size && nmemb > SIZE_MAX / size)
		return (NULL);
	result = malloc(total_size);
	if (!result)
		return (NULL);
	index = 0;
	while (index < total_size)
	{
		((unsigned char *)result)[index] = 0;
		index++;
	}
	return (result);
}
