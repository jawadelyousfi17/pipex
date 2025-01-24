/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:10:56 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 19:23:17 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char *charset, char c)
{
	if (!charset)
		return (0);
	while (*charset)
	{
		if (*charset == c)
			return (c);
		charset++;
	}
	return (0);
}

static int	handle_writing(va_list dest, char c)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr_stdout(va_arg(dest, int)));
	else if (c == 'c')
		return (ft_putchar_stdout(va_arg(dest, int)));
	else if (c == 's')
		return (ft_putstr_stdout(va_arg(dest, char *)));
	else if (c == '%')
		return (ft_putchar_stdout('%'));
	else if (c == 'x')
		return (ft_puthexa(va_arg(dest, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_puthexa(va_arg(dest, unsigned int), "0123456789ABCDEF"));
	else if (c == 'u')
		return (ft_put_unsigned(va_arg(dest, unsigned int)));
	else if (c == 'p')
		return (ft_put_address(va_arg(dest, unsigned long int)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		counter;
	va_list	ptr;

	counter = 0;
	va_start(ptr, s);
	if (write(1, "", 0) == -1)
		return (-1);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			s++;
			if (is_charset("cspdiuxX%", *s))
				counter += handle_writing(ptr, *s);
			else
				counter += ft_putchar_stdout(*s);
		}
		else if (*s == '%' && !*(s + 1))
			break ;
		else
			counter += write(1, s, 1);
		s++;
	}
	va_end(ptr);
	return (counter);
}
