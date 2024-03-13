/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:55:16 by btvildia          #+#    #+#             */
/*   Updated: 2024/02/16 17:57:43 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_char(int c, int i)
{
	i++;
	write(1, &c, 1);
	return (i);
}

int	ft_find_str(char *a, int i)
{
	int	j;

	j = 0;
	if (!a)
	{
		i = ft_find_str("(null)", i);
	}
	else
	{
		while (a[j])
		{
			write(1, &a[j], 1);
			j++;
			i++;
		}
	}
	return (i);
}

int	ft_find_number(int n, int i)
{
	if (n == -2147483648)
	{
		i = ft_find_char('-', i);
		i = ft_find_char('2', i);
		i = ft_find_number(147483648, i);
	}
	else if (n < 0)
	{
		i = ft_find_char('-', i);
		n = -n;
		i = ft_find_number(n, i);
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

int	ft_next_precent(const char *format, va_list args, int j, int i)
{
	if (format[i] == 's')
		j = ft_find_str(va_arg(args, char *), j);
	if (format[i] == 'c')
		j = ft_find_char(va_arg(args, int), j);
	if (format[i] == 'd')
		j = ft_find_number(va_arg(args, int), j);
	if (format[i] == 'i')
		j = ft_find_number(va_arg(args, int), j);
	if (format[i] == 'x')
		j = ft_find_hexlow(va_arg(args, int), j);
	if (format[i] == 'X')
		j = ft_find_hexup(va_arg(args, int), j);
	if (format[i] == '%')
		j = ft_find_char('%', j);
	if (format[i] == 'u')
		j = ft_find_uns(va_arg(args, int), j);
	if (format[i] == 'p')
		j = ft_find_ptr(va_arg(args, unsigned long), j);
	return (j);
}

int	ft_printf(const char *a, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, a);
	while (a[i] != '\0')
	{
		if (a[i] == '%')
		{
			j = ft_next_precent(a, args, j, ++i);
		}
		else
		{
			j++;
			write(1, &a[i], 1);
		}
		i++;
	}
	va_end(args);
	return (j);
}
