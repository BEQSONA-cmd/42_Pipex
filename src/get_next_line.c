/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:42:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/02/16 17:55:01 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*read_full(int fd, char *line)
{
	char	*buff;
	ssize_t	byte;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	byte = 1;
	while (!ft_nline(line, '\n') && byte > 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte < 0)
		{
			free(buff);
			free(line);
			return (NULL);
		}
		buff[byte] = '\0';
		line = ft_reallocate(line, buff);
	}
	free(buff);
	return (line);
}

char	*ft_save(char *buff)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(buff) - i));
	if (!line)
		return (free(buff), NULL);
	i++;
	while (buff[i])
	{
		line[j++] = buff[i++];
	}
	line[j] = '\0';
	free(buff);
	return (line);
}

char	*get_first_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		line[i] = buff[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*fline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fline = read_full(fd, fline);
	if (!fline)
		return (NULL);
	line = get_first_line(fline);
	fline = ft_save(fline);
	return (line);
}
