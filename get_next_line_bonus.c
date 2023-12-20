/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:08:52 by mohimi            #+#    #+#             */
/*   Updated: 2023/12/19 14:46:10 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*find_line(int fd, char *rest, char *buffer)
{
	ssize_t	read_char;
	char	*tmp;

	while (!ft_sersh_for_newline(buffer, '\n'))
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char <= 0)
			break ;
		buffer[read_char] = '\0';
		if (!rest)
			rest = ft_strdup(buffer);
		else
		{
			tmp = rest;
			rest = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}
	free(buffer);
	return (rest);
}

char	*fix_line(char *bufl)
{
	char	*rest;
	size_t	i;

	if (!bufl)
		return (NULL);
	i = 0;
	while (bufl[i] != '\0' && bufl[i] != '\n')
		i++;
	rest = ft_substr(bufl, i + 1, ft_strlen(bufl) - i);
	if (!rest)
		return (NULL);
	if (bufl[i] != 0)
		bufl[i + 1] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (free(rest[fd]), rest[fd] = NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(rest[fd]), rest[fd] = NULL, NULL);
	buffer[0] = 0;
	line = find_line(fd, rest[fd], buffer);
	if (!line)
		return (rest[fd] = NULL, NULL);
	rest[fd] = fix_line(line);
	if (!rest[fd])
		return (free(line), NULL);
	if (line[0] == 0)
		return (free(rest[fd]), free(line), rest[fd] = NULL);
	buffer = ft_strdup(line);
	if (!buffer)
		return (free(line), free(rest[fd]), rest[fd] = NULL, NULL);
	return (free(line), buffer);
}
