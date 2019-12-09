/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:47:29 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/19 22:26:20 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_putstrf(char *s, t_ops *ops)
{
	int			i;

	i = -1;
	while (s[++i])
		ft_putcharf(s[i], ops);
	return (ops->printed);
}

int			ft_ismod(int c)
{
	if (c == 'l' || c == 'h' || c == 'j' || c == 'z')
		return (1);
	else
		return (0);
}

int			ft_putcharf(char c, t_ops *ops)
{
	write(1, &c, 1);
	ops->printed += 1;
	return (ops->printed);
}

size_t		ft_strlenu(unsigned long long n)
{
	size_t		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

long long	ft_strlens(long long n)
{
	long long	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}
