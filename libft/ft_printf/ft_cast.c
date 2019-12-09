/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:47:44 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/19 22:26:02 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			ft_cast(va_list list, t_ops *ops)
{
	long long res;

	if (!ops->mod)
		res = va_arg(list, int);
	else if (ops->mod == 1)
		res = (short int)va_arg(list, int);
	else if (ops->mod == 2)
		res = (char)va_arg(list, int);
	else if (ops->mod == 3)
		res = va_arg(list, long int);
	else if (ops->mod == 4)
		res = va_arg(list, long long int);
	else
		res = 0;
	return (res);
}

unsigned long long	ft_cast_unsigned(va_list list, t_ops *ops)
{
	long long res;

	if (!ops->mod)
		res = va_arg(list, unsigned int);
	else if (ops->mod == 1)
		res = (unsigned short int)va_arg(list, unsigned int);
	else if (ops->mod == 2)
		res = (unsigned char)va_arg(list, unsigned int);
	else if (ops->mod == 3)
		res = va_arg(list, unsigned long int);
	else if (ops->mod == 4)
		res = va_arg(list, unsigned long long int);
	else
		res = 0;
	return (res);
}

void				ft_hash_period(char *temp, t_ops *ops)
{
	if (ops->conversion == 'o' && ops->hash && ops->period)
		temp[0] = '0';
	else if (ops->period == 1 && ops->precision == 0
			&& ops->conversion != 'o')
		temp[0] = 0;
	else if (ops->conversion == 'o' && ops->period)
		temp[0] = 0;
	else
		temp[0] = '0';
	ops->hash = 0;
}

void				ft_check_period(char *str, t_ops *ops)
{
	if (ops->period && ops->precision == 0 && str[0] == '0'
			&& ops->conversion != 'o')
		str[0] = 0;
}

void				ft_check_null(char *temp, int x, t_ops *ops)
{
	if (ops->conversion == 'c' && temp[x] == '\0')
	{
		temp[0] = '^';
		temp[1] = '@';
		ops->printed -= 1;
		ops->width += 1;
	}
}
