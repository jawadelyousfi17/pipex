/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:17:28 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 19:24:07 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_stdout(int c)
{
	return (write(2, &c, 1));
}

static size_t	f_strlen(char *s)
{
	int	counter;

	counter = 0;
	if (!s)
		return (0);
	while (s[counter])
		counter++;
	return (counter);
}

int	ft_putstr_stdout(char *s)
{
	if (!s)
		return (write(2, "(null)", 6));
	return (write(2, s, f_strlen(s)));
}
