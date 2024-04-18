/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:54:16 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/18 20:54:50 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_nline(char *s, int c)
{
	c = (char)c;
	while (1)
	{
		if (!s)
		{
			return (0);
		}
		if (*s == c)
		{
			return ((char *)s);
		}
		if (*s == '\0')
		{
			break ;
		}
		s++;
	}
	return (NULL);
}

char	*ft_strjoin_null(char *s2)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	i;
	char			*a;

	i = 0;
	x = 0;
	y = ft_strlen((char *)s2);
	a = malloc(x + y + 1);
	if (!a)
		return (NULL);
	a[i] = '\0';
	while (s2[i] != '\0')
	{
		a[x + i] = s2[i];
		i++;
	}
	a[x + i] = '\0';
	return (a);
}

char	*ft_reallocate(char *s1, char *s2)
{
	char	*str;

	if (!s1)
		str = ft_strjoin_null(s2);
	else
		str = ft_strjoin(s1, s2);
	free(s1);
	s1 = str;
	return (s1);
}
