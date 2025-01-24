/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:14:53 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 19:23:24 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_get_address_size(unsigned long int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		counter++;
		n /= 16;
	}
	return (counter);
}

static void	_ft_put_address_h(unsigned long int n)
{
	if (n > 15)
	{
		_ft_put_address_h(n / 16);
		_ft_put_address_h(n % 16);
	}
	else
		ft_putchar_stdout("0123456789abcdef"[n]);
}

int	ft_put_address(unsigned long int n)
{
	int	counter;

	counter = _get_address_size(n);
	counter += ft_putstr_stdout("0x");
	_ft_put_address_h(n);
	return (counter);
}
