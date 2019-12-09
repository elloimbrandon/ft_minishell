/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:40:03 by brfeltz           #+#    #+#             */
/*   Updated: 2019/03/16 13:49:20 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_do_op(char *nbr1, char op, char *nbr2)
{
	int	nb1;
	int nb2;
	int r;

	nb1 = ft_atoi(nbr1);
	nb2 = ft_atoi(nbr2);
	r = 0;
	if (op == '+')
		r = nb1 + nb2;
	if (op == '-')
		r = nb1 - nb2;
	if (op == '*')
		r = nb1 * nb2;
	if (op == '%' && nb2 != 0)
		r = nb1 % nb2;
	if (op == '/' && nb2 != 0)
		r = nb1 / nb2;
	return (r);
}
