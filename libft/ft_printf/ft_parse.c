/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:32:40 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/19 21:39:00 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_mods(char *format, t_ops *ops, int *i)
{
	int		x;

	x = *i;
	if (ft_ismod(format[x]))
	{
		if (format[x] == 'h' && format[x + 1] != 'h')
			ops->mod = 1;
		else if (format[x] == 'h' && format[x + 1] == 'h')
		{
			ops->mod = 2;
			x += 1;
		}
		else if (format[x] == 'l' && format[x + 1] != 'l')
			ops->mod = 3;
		else if (format[x] == 'l' && format[x + 1] == 'l')
		{
			ops->mod = 4;
			x += 1;
		}
		x++;
	}
	*i = x;
}

int		ft_check_flags2(char *format, t_ops *ops, int x)
{
	if (format[x] == ' ')
		ops->space = 1;
	else if (format[x] == '-')
		ops->minus = 1;
	else if (format[x] == '+')
		ops->add = 1;
	else if (format[x] == '0')
		ops->zero = 1;
	else if (format[x] == '#')
		ops->hash = 1;
	else if (format[x] == '.')
	{
		ops->period = 1;
		ops->precision = ft_atoi(&format[x + 1]);
		while (ft_isdigit(format[x + 1]))
			x++;
	}
	else if (ft_atoi(&format[x]))
	{
		ops->width = ft_atoi(&format[x]);
		while (ft_isdigit(format[x + 1]))
			x++;
	}
	return (x);
}

void	ft_check_flags(char *format, t_ops *ops, int *i)
{
	int		x;

	x = *i;
	while (!ft_isalpha(format[x]) && format[x])
	{
		if (format[x] == '%')
		{
			ops->conversion = '%';
			break ;
		}
		x = ft_check_flags2(format, ops, x);
		x++;
	}
	*i = x;
}

int		ft_check_conversion(int i, char *format, char c, t_ops *ops)
{
	while (format[++i])
		if (c == format[i])
			ops->conversion = c;
	return (ops->conversion ? 1 : 0);
}
