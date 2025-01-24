/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:17:05 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 19:23:45 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_get_unsigned_size(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

static void	_ft_putunsigned_h(unsigned int n)
{
	if (n > 9)
	{
		_ft_putunsigned_h(n / 10);
		_ft_putunsigned_h(n % 10);
	}
	else
		ft_putchar_stdout(n + 48);
}

int	ft_put_unsigned(unsigned int n)
{
	int	counter;

	_ft_putunsigned_h(n);
	counter = _get_unsigned_size(n);
	return (counter);
}
