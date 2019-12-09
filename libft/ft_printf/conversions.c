/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:16:53 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/07 23:36:41 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_tobinary(unsigned long long nbr)
{
	char				*str;
	int					len;
	int					i;

	len = ft_strlenu(nbr);
	str = (char*)malloc(sizeof(char) * len);
	i = 0;
	while (nbr > 0)
	{
		if (nbr % 2 == 0)
			str[i] = '0';
		else
			str[i] = '1';
		nbr /= 2;
		i++;
	}
	str[i] = '\0';
	str = ft_strrev(str);
	return (str);
}

char		*ft_unlltoa(unsigned long long nbr)
{
	char				*str;
	int					len;
	unsigned long long	sign;

	len = ft_strlenu(nbr);
	sign = nbr;
	str = (char*)malloc(sizeof(char) * len);
	if (!str[0])
		str[0] = '0';
	str[len] = '\0';
	str[--len] = sign % 10 + '0';
	while (sign /= 10)
		str[--len] = sign % 10 + '0';
	return (str);
}

char		*ft_itoall(long long n)
{
	char				*str;
	int					len;
	long long			sign;

	len = ft_strlens(n);
	sign = n;
	if (n < 0)
	{
		sign = -n;
		len++;
	}
	str = (char*)malloc(sizeof(char) * len);
	if (!str[0])
		str[0] = '0';
	str[len] = '\0';
	str[--len] = sign % 10 + '0';
	while (sign /= 10)
		str[--len] = sign % 10 + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}

char		*ft_itoabase(unsigned long long nbr, int base,
			t_ops *ops, char *str)
{
	int					i;

	i = 0;
	if (!str)
		str[0] = '0';
	if (ops->conversion == 'o' || ops->conversion == 'x'
			|| ops->conversion == 'p')
	{
		while (nbr)
		{
			str[i++] = "0123456789abcdef"[nbr % base];
			(nbr /= base);
		}
	}
	else if (ops->conversion == 'X')
	{
		while (nbr)
		{
			str[i++] = "0123456789ABCDEF"[nbr % base];
			nbr /= base;
		}
	}
	if ((ops->conversion == 'p' || ops->hash == 1) && ops->width == 0)
		ft_add_hash(ops, str);
	return (ft_strrev(str));
}

void		ft_add_hash(t_ops *ops, char *str)
{
	ops->hashplaced = 1;
	if ((ops->conversion == 'x' || ops->conversion == 'X'
			|| ops->conversion == 'p') && ops->hash)
		ft_strcat(str, ops->conversion == 'X' ? "X0" : "x0");
	else if (ops->hash)
		ft_strcat(str, "0");
}
