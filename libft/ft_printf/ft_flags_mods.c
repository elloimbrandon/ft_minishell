/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_mods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:28:09 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/19 22:34:56 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flag_mods(t_ops *ops, char *str, char *output)
{
	t_vals	vals;
	t_vals	wvals;

	ft_bzero(&vals, sizeof(t_vals));
	ft_bzero(&wvals, sizeof(t_vals));
	output = ft_strnew(4864);
	ft_check_period(str, ops);
	if (ops->conversion != 'c' && ops->conversion != '%')
	{
		str = precision_flags(ops, str);
		wvals.length = ft_strlen(str);
		if (!ops->hashplaced && (ops->hash || ops->conversion == 'p'))
			ops->width -= (ops->conversion == 'o' ? 1 : 2);
		if (ops->space && str[0] != '-' && str[0] != '+'
				&& ops->conversion != 'u')
			str = check_space(str, ops);
		output = width_flags(output, str, ops, &wvals);
	}
	if (ops->zero != 1 && (ops->conversion == 'c' || ops->conversion == '%'))
	{
		wvals.length = ft_strlen(str);
		output = width_flags(output, str, ops, &wvals);
	}
	ops->printed = ft_putstrf(output, ops);
	return (ops->printed);
}

char	*check_space(char *str, t_ops *ops)
{
	char	*newstr;

	newstr = ft_strnew(ft_strlen(str));
	if (ops->space == 1 && !ops->minus && !ops->width)
	{
		newstr[0] = ' ';
		ft_strncat(newstr, str, ft_strlen(str));
	}
	else if (ops->space == 1 && ops->minus && !ops->add)
	{
		newstr[0] = '-';
		ft_strncat(newstr, str, ft_strlen(str));
	}
	else
		return (str);
	return (newstr);
}

char	*precision_flags(t_ops *ops, char *str)
{
	char	*temp;
	t_vals	vals;

	temp = ft_strnew(ft_strlen(str) + ops->precision);
	temp = no_perc_width(temp, str, ops);
	check_prec_flag(ops, temp, 0);
	if (temp[0] == ft_isflag(temp[0]))
	{
		vals = prec_checker(temp, str, ops);
		while (ops->precision-- > vals.length && ops->conversion != 's')
			temp[vals.x++] = (ops->zero ||
					conversion_check("diouxXfb", ops->conversion) ? '0' : ' ');
		if (conversion_check("diouxXfb", ops->conversion) == 1)
			ops->precision = ft_strlen(str);
		while (str[vals.i] && ops->precision >= 0)
		{
			temp[vals.x++] = str[vals.i++];
			if (conversion_check("cs%", ops->conversion) == 1)
				ops->precision--;
		}
	}
	return (temp);
}

char	*width_flags(char *output, char *str, t_ops *ops, t_vals *wvals)
{
	ft_width_check(output, str, ops, wvals);
	while (!ops->width && str[wvals->x] && output[wvals->i])
		output[wvals->i++] = str[wvals->x++];
	while (!ops->minus && ops->width-- > wvals->length)
		output[wvals->i++] = (ops->zero ? '0' : ' ');
	if ((ops->hash || ops->conversion == 'p') && ops->width && !ops->hashplaced)
	{
		if (ops->conversion != 'o' && ops->hash)
		{
			ft_strcat(output, ops->conversion == 'X' ? "0X" : "0x");
			wvals->i += 2;
		}
		else
			output[wvals->i++] = '0';
	}
	while (str[wvals->x])
		output[wvals->i++] = str[wvals->x++];
	while (ops->minus && ops->width-- > wvals->length)
		output[wvals->i++] = (ops->zero ? '0' : ' ');
	return (output);
}

char	*no_perc_width(char *temp, char *str, t_ops *ops)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (ft_isflag(str[i]) && ops->conversion == 's' && ops->precision == 0)
		temp[x++] = str[i++];
	while (str[i] && ops->conversion == 'p' && ops->precision == 0)
		temp[x++] = str[i++];
	return (!str ? 0 : temp);
}
