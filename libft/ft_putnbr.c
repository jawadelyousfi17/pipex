/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:15:45 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 19:23:38 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_size(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		counter++;
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

static void	ft_putnbr_h(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	if (n > 9)
	{
		ft_putnbr_h(n / 10);
		ft_putnbr_h(n % 10);
	}
	else
		ft_putchar_stdout(n + 48);
}

int	ft_putnbr_stdout(int n)
{
	ft_putnbr_h(n);
	return (get_int_size(n));
}
