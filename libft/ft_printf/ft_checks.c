/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:46:28 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/19 22:25:24 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conversion_check(char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

t_vals	prec_checker(char *temp, char *str, t_ops *ops)
{
	int	i;
	int	x;
	int	length;

	i = 0;
	x = 0;
	length = ft_strlen(str);
	if (length == 1 && ops->minus)
	{
		length++;
		ops->precision++;
	}
	else if (str[i] == '-')
	{
		temp[x++] = '-';
		ops->precision++;
		i++;
	}
	else if (ops->add && ops->conversion != 'u')
	{
		temp[x] = '+';
		i++;
	}
	return ((t_vals){x, i, length});
}

void	ft_width_check(char *output, char *str, t_ops *ops, t_vals *wvals)
{
	if (str[0] == '-' && ops->zero)
	{
		output[0] = '-';
		wvals->i++;
		wvals->x++;
	}
	else if (ops->add && str[0] != '-' && ops->zero)
	{
		output[0] = '+';
		wvals->i++;
		wvals->x++;
	}
	if (ops->hash && conversion_check("xXpo", ops->conversion) && ops->zero)
	{
		ft_strcat(output, ops->conversion == 'X' ? "0X" : "0x");
		wvals->i += 2;
		ops->hashplaced = 1;
	}
}

char	check_prec_flag(t_ops *ops, char *temp, int x)
{
	if (ops->minus && (!conversion_check("sp", ops->conversion)))
		return (temp[x] = '-');
	else if (ops->add && (ops->minus == 0))
		return (temp[x] = '+');
	else if (ops->add && (!conversion_check("sp", ops->conversion)))
		return (temp[x] = '+');
	else if (ops->space && (ops->minus == 0))
		return (temp[x] = ' ');
	else
		return (0);
}

char	ft_isflag(char x)
{
	return (x == '-' || x == '+' || x == ' ' || x == '0' || x == 0 ? x : 1);
}
