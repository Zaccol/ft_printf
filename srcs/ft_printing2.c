/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:00:31 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/06 20:10:58 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	my_printf_unsigned(va_list *my_list, t_form *spec)
{
	unsigned int	num;
	int				numlen;
	int				negnum;

	num = va_arg(*my_list, unsigned int);
	num = 4294967296 - (num * -1);
	negnum = 0;
	if (num == 0)
		numlen = 1;
	else
		numlen = intlen_unsigned(num);
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

void	my_printf_hexa(va_list *my_list, t_form *spec)
{
	unsigned int	num;
	int				numlen;
	int				negnum;

	num = va_arg(*my_list, unsigned int);
	negnum = 0;
	if (num == 0)
		numlen = 1;
	else
		numlen = intlen_base(num, "0123456789abcdef", 0);
	if (spec->precision > numlen)
		spec->field_print = spec->field - spec->precision;
	else
		spec->field_print = spec->field - numlen;
	spec->precision_print = spec->precision - numlen;
	printed_count(spec);
	if (spec->minus == 0)
		print_nbr_standard(spec, negnum, num);
	if (spec->minus == 1)
		print_nbr_minus(spec, negnum, num);
}

void	my_printf_ptr(va_list *my_list, t_form *spec)
{
	unsigned long long	num;
	int					numlen;

	num = va_arg(*my_list, unsigned long long);
	if (num == 0)
		numlen = 1;
	else
		numlen = (intlen_base(num, "0123456789abcdef", 0));
	if (spec->precision > numlen)
		spec->field_print = spec->field - spec->precision - 2;
	else
		spec->field_print = spec->field - numlen - 2;
	spec->precision_print = spec->precision - numlen;
	printed_count(spec);
	if (spec->minus == 0)
		print_nbr_standard_ptr(spec, num);
	if (spec->minus == 1)
		print_nbr_minus_ptr(spec, num);
}

int	condition(const char *src, t_form *spec, int percent)
{
	if ((spec->i != 0 && src[spec->i - 1] == '%'
			&& ((src[spec->i] >= '0' && src[spec->i] <= '9')
				|| src[spec->i] == '-' || src[spec->i] == '*'
				|| src[spec->i] == '.' || src[spec->i] == 'c'
				|| src[spec->i] == 's' || src[spec->i] == 'p'
				|| src[spec->i] == 'd' || src[spec->i] == 'i'
				|| src[spec->i] == 'u' || src[spec->i] == 'x'
				|| src[spec->i] == 'X' || src[spec->i] == '+'
				|| src[spec->i] == ' ' || src[spec->i] == '#'))
		&& (percent % 2) != 0)
		return (1);
	return (0);
}
