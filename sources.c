/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:51:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/31 20:52:33 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	char_error(char c)
{
	write(2, &c, 1);
}

void	std_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		char_error(str[i]);
		i++;
	}
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

void	ft_no_command(char *cmd)
{
	std_error(cmd);
	std_error(": command not found\n");
	exit(127);
}

void	ft_no_file(char *arg)
{
	std_error(arg);
	std_error(": No such file or directory\n");
	exit(1);
}

void	ft_error(char *str)
{
	std_error(str);
	exit(1);
}
