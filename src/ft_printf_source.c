/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:31:55 by btvildia          #+#    #+#             */
/*   Updated: 2024/02/18 00:40:16 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_hexlow(size_t n, int i)
{
	unsigned int	j;

	j = (unsigned int)n;
	if (j == 0)
		i = ft_find_char('0', i);
	else if (j >= 16)
	{
		i = ft_find_hexlow(j / 16, i);
		i = ft_find_hexlow(j % 16, i);
	}
	else
	{
		if (n <= 9)
			i = ft_find_char(n + '0', i);
		else
			i = ft_find_char(n + 'a' - 10, i);
	}
	return (i);
}

int	ft_find_hexup(size_t n, int i)
{
	unsigned int	j;

	j = (unsigned int)n;
	if (j == 0)
		i = ft_find_char('0', i);
	else if (j >= 16)
	{
		i = ft_find_hexup(j / 16, i);
		i = ft_find_hexup(j % 16, i);
	}
	else
	{
		if (n <= 9)
			i = ft_find_char(n + '0', i);
		else
			i = ft_find_char(n + 'A' - 10, i);
	}
	return (i);
}

int	ft_find_uns(unsigned int n, int i)
{
	if (n == 0)
	{
		i = ft_find_char('0', i);
		return (i);
	}
	else if (n >= 10)
	{
		i = ft_find_number((n / 10), i);
		i = ft_find_number((n % 10), i);
	}
	else
	{
		i = ft_find_char(((n % 10) + '0'), i);
	}
	return (i);
}

int	ft_ptr(unsigned long nb, int j)
{
	if (nb >= 16)
	{
		j = ft_ptr((nb / 16), j);
		j = ft_ptr((nb % 16), j);
	}
	else
	{
		if (nb <= 9)
			j = ft_find_char((nb + '0'), j);
		else
			j = ft_find_char((nb - 10 + 'a'), j);
	}
	return (j);
}

int	ft_find_ptr(unsigned long ptr, int j)
{
	j = ft_find_str("0x", j);
	if (ptr == 0)
		j = ft_find_char('0', j);
	else
	{
		j = ft_ptr(ptr, j);
	}
	return (j);
}
