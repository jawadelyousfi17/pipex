/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:13:45 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 19:23:33 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_get_hexa_size(unsigned int n)
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

static void	_ft_puthexa_h(unsigned int n, char *base)
{
	if (!base)
		return ;
	if (n > 15)
	{
		_ft_puthexa_h(n / 16, base);
		_ft_puthexa_h(n % 16, base);
	}
	else
		ft_putchar_stdout(base[n]);
}

int	ft_puthexa(unsigned int n, char *base)
{
	_ft_puthexa_h(n, base);
	return (_get_hexa_size(n));
}
