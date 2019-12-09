/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:48:31 by brfeltz           #+#    #+#             */
/*   Updated: 2019/08/19 22:36:00 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <inttypes.h>
# include <locale.h>
# include <math.h>
# include "../libft.h"

/*
** Macros
*/

# define LONG_LONG_MAX 9223372036854775807 - 1
# define LONG_LONG_MIN -9223372036854775807 - 1
# define MAX_INT 2147483647 - 1
# define MIN_INT -2147483647 - 1

# define FLAGS(x) (x == '-' || x == '+' || x == '0' || x == ' ')

/*
** Struct
*/

typedef	struct		s_vals
{
	int				i;
	int				x;
	int				length;
}					t_vals;

typedef	struct		s_operations
{
	int				nbr;
	int				add;
	int				minus;
	int				hash;
	int				space;
	int				zero;
	int				width;
	int				mod;
	int				printed;
	int				hashplaced;
	int				period;
	int				precision;
	char			conversion;

}					t_ops;

/*
** Functions
*/

char				ft_isflag(char x);
char				*ft_tobinary(unsigned long long nbr);
char				*ft_itoall(long long n);
char				*ft_itoabase(unsigned long long nbr, int base,
					t_ops *ops, char *str);
char				*ft_unlltoa(unsigned long long nbr);
char				*no_perc_width(char *temp, char *str, t_ops *ops);
char				*width_flags(char *output, char *str,
					t_ops *ops, t_vals *vals);
char				*precision_flags(t_ops *ops, char *str);
char				check_prec_flag(t_ops *ops, char *temp, int x);
char				*check_space(char *str, t_ops *ops);
int					ft_handle_all(const char *format, va_list list,
					int i, t_ops ops);
int					conversion_check(char *str, char c);
int					flag_mods(t_ops *ops, char *str, char *output);
int					ft_ismod(int c);
int					handle_int(va_list list, t_ops *ops);
int					handle_unll(va_list list, t_ops *ops);
int					handle_char(va_list list, t_ops *ops);
int					handle_oc_hex_ptr(va_list list, t_ops *ops);
int					ft_putcharf(char c, t_ops *ops);
int					ft_printf(const char *format, ...);
int					ft_parse(const char *format, int *i, t_ops *ops);
int					ft_check_flags2(char *format, t_ops *ops, int x);
int					ft_check_conversion(int i, char *format,
					char c, t_ops *ops);
int					ft_putstrf(char *s, t_ops *ops);
size_t				ft_strlenu(unsigned long long n);
t_vals				prec_checker(char *temp, char *str, t_ops *ops);
void				ft_hash_period(char *temp, t_ops *ops);
void				ft_check_null(char *temp, int x, t_ops *ops);
void				ft_check_period(char *str, t_ops *ops);
void				ft_check_flags(char *format, t_ops *ops, int *i);
void				ft_check_mods(char *format, t_ops *ops, int *i);
void				ft_width_check(char *output, char *str,
					t_ops *ops, t_vals *wvals);
void				ft_add_hash(t_ops *ops, char *str);
void				ft_putnbrf(int nbr);
long long			ft_cast(va_list list, t_ops *ops);
long long			ft_strlens(long long n);
unsigned long long	ft_cast_unsigned(va_list list, t_ops *ops);

#endif
