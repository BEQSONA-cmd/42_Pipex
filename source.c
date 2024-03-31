/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:19:59 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/31 20:54:44 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	x;
	unsigned int	y;
	char			*a;
	unsigned int	i;

	if (s1 == NULL && s2 == NULL)
	{
		return (NULL);
	}
	x = (s1 != NULL) ? ft_strlen(s1) : 0;
	y = (s2 != NULL) ? ft_strlen(s2) : 0;
	a = malloc(x + y + 1);
	if (!a)
	{
		return (NULL);
	}
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

char	*ft_strdup(char *s1)
{
	unsigned int	j;
	unsigned int	i;
	char			*a;

	j = ft_strlen(s1);
	i = 0;
	a = malloc(((j) * sizeof(char)) + 1);
	if (s1 == NULL)
		return (malloc(0));
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

char	**ft_split(char *a, char d)
{
	int		i;
	int		j;
	int		x;
	char	**c;

	i = 0;
	j = 0;
	x = 0;
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
	if (!c)
		return (NULL);
	i = 0;
	j = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		j = i;
		while (a[i] && a[i] != d)
			i++;
		if (i > j)
		{
			c[x] = malloc(sizeof(char) * (i - j + 1));
			if (!c[x])
			{
				while (x > 0)
				{
					free(c[x - 1]);
					x--;
				}
				free(c);
				return (NULL);
			}
			ft_strncpy(c[x], &a[j], i - j);
			c[x][i - j] = '\0';
			x++;
		}
	}
	c[x] = NULL;
	return (c);
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
