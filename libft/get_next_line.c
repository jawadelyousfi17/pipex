/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:55:15 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 18:59:44 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*clean_memory(char **reserve, char **line)
{
	free(*reserve);
	free(*line);
	*line = NULL;
	*reserve = NULL;
	return (NULL);
}

static int	read_data(int fd, char *buffer, char **reserve)
{
	int		read_count;
	char	*tmp;

	read_count = read(fd, buffer, BUFFER_SIZE);
	if (read_count < 0)
		return (read_count);
	buffer[read_count] = '\0';
	tmp = ft_strjoin(*reserve, buffer);
	if (!tmp)
		return (-1);
	free(*reserve);
	*reserve = tmp;
	return (read_count);
}

static void	extract_line(char **reserve, char **line, int *read_count)
{
	char	*tmp;
	int		line_len;

	tmp = ft_strchr(*reserve, '\n');
	if (!tmp && *read_count > 0)
		return ;
	if (!tmp && *read_count == 0)
	{
		*line = *reserve;
		*reserve = NULL;
		return ;
	}
	line_len = tmp - *reserve - 1;
	tmp = ft_substr(tmp + 1, 0, ft_strlen(tmp + 1) + 1);
	*line = ft_substr(*reserve, 0, line_len + 1);
	if (!*line || !tmp)
	{
		*read_count = -1;
		free(tmp);
		return ;
	}
	free(*reserve);
	*reserve = tmp;
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*buffer;
	int			read_count;
	char		*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (!line)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (clean_memory(&reserve, &line));
		read_count = read_data(fd, buffer, &reserve);
		free(buffer);
		if (read_count < 0 || ft_strlen(reserve) == 0)
			return (clean_memory(&reserve, &line));
		extract_line(&reserve, &line, &read_count);
		if (read_count < 0)
			return (clean_memory(&reserve, &line));
	}
	return (line);
}
