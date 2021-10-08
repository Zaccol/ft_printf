/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:00:31 by lzaccome          #+#    #+#             */
/*   Updated: 2021/09/30 22:57:03 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	write_str(int precision_print, int field_print, t_form *spec, char *src)
{
	if (spec->minus == 0)
	{
		while (field_print-- > 0 && spec->field != 0)
			write(1, " ", 1);
		write(1, src, precision_print);
	}
	if (spec->minus == 1)
	{
		write(1, src, precision_print);
		while (field_print-- > 0 && spec->field != 0)
			write(1, " ", 1);
	}
}

void	my_printf_str(va_list *my_list, t_form *spec)
{
	char	*src;
	int		field_print;
	int		precision_print;
	int		srclen;

	src = va_arg(*my_list, char *);
	if (src == NULL)
		src = "(null)";
	srclen = strlen(src);
	if (spec->precision < srclen && spec->point == 1)
		precision_print = spec->precision;
	else
		precision_print = srclen;
	field_print = spec->field - precision_print;
	if (field_print < 0)
		field_print = 0;
	if (precision_print < 0)
		precision_print = 0;
	spec->printed += precision_print + field_print;
	write_str(precision_print, field_print, spec, src);
}

void	my_printf_char(va_list *my_list, t_form *spec)
{
	char	c;
	int		field_print;

	c = va_arg(*my_list, int);
	field_print = spec->field - 1;
	if (field_print < 0)
		field_print = 0;
	spec->printed += field_print + 1;
	if (spec->minus == 0)
	{
		while (field_print-- > 0)
			write(1, " ", 1);
		write(1, &c, 1);
	}
	if (spec->minus == 1)
	{
		write(1, &c, 1);
		while (field_print-- > 0)
			write(1, " ", 1);
	}
}

long	fill_nbr(long num, int *negnum, t_form *spec)
{
	if (num < 0)
	{
		num = -num;
		spec->field_print--;
		*negnum = 1;
		spec->printed++;
	}
	if (num == 0 && spec->precision == 0 && spec->point == 1)
	{
		spec->zero = 0;
		spec->field_print++;
		spec->p_case = 1;
	}
	return (num);
}

void	my_printf_nbr(va_list *my_list, t_form *spec)
{
	long	num;
	long	numlen;
	int		negnum;

	num = va_arg(*my_list, int);
	negnum = 0;
	if (num == 0)
		numlen = 1;
	else
		numlen = intlen(num);
	if (spec->precision > numlen)
		spec->field_print = spec->field - spec->precision;
	else
		spec->field_print = spec->field - numlen;
	spec->precision_print = spec->precision - numlen;
	num = fill_nbr(num, &negnum, spec);
	printed_count(spec);
	if (spec->minus == 0)
		print_nbr_standard(spec, negnum, num);
	if (spec->minus == 1)
		print_nbr_minus(spec, negnum, num);
}
