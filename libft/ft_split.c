/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:29:26 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/15 11:42:01 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	in_word;
	int	counter;

	counter = 0;
	in_word = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
		{
			str++;
			in_word = 1;
		}
		if (in_word)
		{
			counter++;
			in_word = 0;
		}
	}
	return (counter);
}

static char	**__free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (NULL);
}

static char	**zero_last(char **splited_strings, int index)
{
	splited_strings[index] = 0;
	return (splited_strings);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_string;
	int		start_index;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	start_index = 0;
	splited_string = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!splited_string)
		return (NULL);
	while (s && *s)
	{
		start_index = 0;
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		while (*s && *s != c && ++start_index)
			s++;
		splited_string[index] = ft_substr(s - start_index, 0, start_index);
		if (!splited_string[index++])
			return (__free(splited_string));
	}
	return (zero_last(splited_string, index));
}
