/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:51:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/01 20:51:07 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			free_array(paths);
			return (c);
		}
		free(c);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	ft_error_exit(char *str, char *str2, int status)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(2, "pipex: ", 7);
		write(2, str2, ft_strlen(str2));
		exit(1);
	}
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	exit(status);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_put(char **c, char *a, char d)
{
	int	x;
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		j = i;
		while (a[i] && a[i] != d)
			i++;
		if (i > j)
		{
			c[x] = malloc(sizeof(char) * (i - j) + 1);
			ft_strncpy(c[x], &a[j], i - j);
			x++;
		}
	}
	c[x] = NULL;
	return (c);
}

char	**ft_split(char *a, char d)
{
	int		j;
	int		i;
	char	**c;

	i = 0;
	j = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		if (a[i])
			j++;
		while (a[i] && a[i] != d)
			i++;
	}
	c = malloc(sizeof(char *) * (j + 1));
	c = ft_put(c, a, d);
	return (c);
}
