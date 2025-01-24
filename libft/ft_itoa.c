/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:37:42 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/11 11:00:21 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_size(long int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	int			nbr_size;
	char		*result;

	nbr = n;
	nbr_size = get_int_size(nbr);
	if (n < 0)
		nbr = -nbr;
	if (n < 0)
		nbr_size++;
	result = (char *)malloc((nbr_size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[nbr_size--] = '\0';
	while (nbr_size >= 0)
	{
		result[nbr_size--] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
