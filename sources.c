/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:51:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/14 18:27:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_array(char **arr, int j)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("cmd[%d] = %s\n", j + 1, arr[i]);
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

void	ft_error(char *str)
{
	ft_printf("%s", str);
	exit(1);
}
