/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:02:47 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/01 19:09:38 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	unsigned int	j;
	unsigned int	i;
	char			*a;

	j = ft_strlen(s1);
	i = 0;
	if (s1 == NULL)
		return (NULL);
	a = malloc(sizeof(char) * (j + 1));
	if (a == NULL)
		return (NULL);
	while (i < j)
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s2[i] != '\0' && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	x;
	unsigned int	y;
	char			*a;
	unsigned int	i;

	x = ft_strlen(s1);
	y = ft_strlen(s2);
	a = malloc(x + y + 1);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			a[i] = s1[i];
			i++;
		}
	}
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		a[x + i] = s2[i];
		i++;
	}
	a[x + i] = '\0';
	return (a);
}
