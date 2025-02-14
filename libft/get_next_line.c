/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:17:09 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/20 17:01:50 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *buff)
{
	char	*buffer;
	char	*line;
	int		bytes_read;

	if (!buff)
		buff = ft_calloc(1, 1);
	if (!buff)
		return (NULL);
	line = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!line)
		return (free(buff), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buff, '\n'))
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), free(buff), NULL);
		line[bytes_read] = '\0';
		buffer = ft_strjoin(buff, line);
		free(buff);
		if (!buffer)
			return (free(line), NULL);
		buff = buffer;
	}
	return (free(line), buff);
}

char	*get_line2(char *buff)
{
	char	*result;
	int		i;

	if (!buff || buff[0] == '\0')
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	result = ft_calloc(sizeof(char), i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		result[i] = buff[i];
		i++;
	}
	if (buff[i])
		result[i] = '\n';
	else
		result[i] = '\0';
	return (result);
}

char	*next_line(char *buff)
{
	char	*result;
	int		y;
	int		i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	if (i == (int)ft_strlen(buff))
		return (free(buff), NULL);
	result = ft_calloc(sizeof(char), ft_strlen(buff) - i + 1);
	if (!result)
		return (free(buff), NULL);
	y = 0;
	while (buff[i])
	{
		result[y] = buff[i];
		i++;
		y++;
	}
	free(buff);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line2(buffer);
	if (!line)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = next_line(buffer);
	return (line);
}

