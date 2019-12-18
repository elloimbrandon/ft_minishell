/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:06:56 by brfeltz           #+#    #+#             */
/*   Updated: 2019/12/18 15:29:29 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** %[parameter][flags][width][.precision][length] type
*/

/*
** BROKEN-> (' ' space flag, b flag(leaks/double-free), long long max, p flag)
** [[also watch some mixed flags]]
*/

int		ft_apply_conversion(va_list list, t_ops *ops)
{
	if (ops->conversion == 's' || ops->conversion == 'c' ||
			ops->conversion == '%')
		ops->printed = handle_char(list, ops);
	if (ops->conversion == 'd' || ops->conversion == 'i' ||
			ops->conversion == 'b' || ops->conversion == 'f')
		ops->printed = handle_int(list, ops);
	if (ops->conversion == 'p' || ops->conversion == 'o'
			|| ops->conversion == 'x' || ops->conversion == 'X')
		ops->printed = handle_oc_hex_ptr(list, ops);
	if (ops->conversion == 'u')
		ops->printed = handle_unll(list, ops);
	return (ops->printed);
}

int		ft_parse(const char *format, int *i, t_ops *ops)
{
	ft_check_flags((char*)format, ops, i);
	ft_check_mods((char*)format, ops, i);
	if (ops->precision > 0 && ops->zero)
		ops->zero = 0;
	if (ops->minus && ops->zero)
		ops->zero = 0;
	if (ft_check_conversion(-1, "scpfdiouxXb", format[*i], ops))
		return (1);
	else
		return (0);
}

int		ft_handle_all(const char *format, va_list list, int i, t_ops ops)
{
	int		res;

	res = 0;
	while (format[++i])
	{
		ft_bzero(&ops, sizeof(t_ops));
		if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putcharf(format[i + 1], &ops);
			i += 1;
			res++;
		}
		else if (format[i] == '%' && format[i + 1] != '%')
		{
			i += 1;
			if (ft_parse(format, &i, &ops) == 1)
				res += ft_apply_conversion(list, &ops);
		}
		else
		{
			ft_putcharf(format[i], &ops);
			res++;
		}
	}
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list	list;
	t_ops	ops;
	int		res;
	int		i;

	i = -1;
	res = 0;
	ft_bzero(&ops, sizeof(t_ops));
	va_start(list, format);
	res = ft_handle_all(format, list, i, ops);
	va_end(list);
	return (res);
}
