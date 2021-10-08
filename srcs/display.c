/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:53:07 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/06 18:57:30 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_nbr_prefix(t_form *spec, int negnum, unsigned int num)
{
	if (negnum == 1 && spec->precision == 0 && spec->field != 0
		&& spec->zero != 1)
		write (1, "-", 1);
	if (negnum == 1 && spec->precision != 0)
		write (1, "-", 1);
	if (negnum == 0 && (spec->more == 1 || spec->space == 1))
	{
		if (spec->more)
			write (1, "+", 1);
		else
			write (1, " ", 1);
		if (spec->field == 0)
			spec->printed += 1;
	}
	if ((spec->format == 'x' || spec->format == 'X')
		&& spec->sharp == 1 && num != 0)
	{
		if (spec->format == 'x')
			write (1, "0x", 2);
		else
			write (1, "0X", 2);
		if (spec->field == 0)
			spec->printed += 2;
	}
}

void	print_nbr_standard(t_form *spec, int negnum, unsigned int num)
{
	char	fill;

	fill = ' ';
	if (spec->zero == 1 && spec->precision == 0)
		fill = '0';
	if (negnum == 1 && spec->precision == 0 && (spec->field == 0
			|| spec->zero == 1))
		write (1, "-", 1);
	if ((spec->more == 1 || spec->space == 1) && spec->field != 0)
		spec->field_print--;
	if (spec->sharp == 1 && spec->field != 0)
		spec->field_print -= 2;
	while (spec->field_print-- > 0 && spec->field != 0)
		write(1, &fill, 1);
	print_nbr_prefix(spec, negnum, num);
	while (spec->precision_print-- > 0)
		if (spec->precision_print >= 0)
			write(1, "0", 1);
	if ((spec->format == 'd' || spec->format == 'i' || spec->format == 'u')
		&& spec->p_case == 0)
		ft_putnbr_base(num, "0123456789", spec);
	if (spec->format == 'x')
		ft_putnbr_base(num, "0123456789abcdef", spec);
	if (spec->format == 'X')
		ft_putnbr_base(num, "0123456789ABCDEF", spec);
}

void	print_nbr_minus(t_form *spec, int negnum, unsigned int num)
{
	char	fill;
	int		tmp;

	fill = ' ';
	tmp = spec->precision_print;
	if (negnum == 1)
		write (1, "-", 1);
	while (tmp-- > 0)
		write(1, "0", 1);
	if ((spec->format == 'd' || spec->format == 'i' || spec->format == 'u')
		&& spec->p_case == 0)
		ft_putnbr_base(num, "0123456789", spec);
	if (spec->format == 'x')
		ft_putnbr_base(num, "0123456789abcdef", spec);
	if (spec->format == 'X')
		ft_putnbr_base(num, "0123456789ABCDEF", spec);
	while (spec->field_print-- > 0 && spec->field != 0)
		if (spec->precision_print >= 0 || spec->precision <= spec->field)
			write(1, &fill, 1);
}

void	print_nbr_standard_ptr(t_form *spec, unsigned long long num)
{
	char	fill;

	fill = ' ';
	if (spec->zero == 1 && spec->precision == 0)
		fill = '0';
	while (spec->field_print-- > 0 && spec->field != 0)
		write(1, &fill, 1);
	write(1, "0x", 2);
	spec->printed += 2;
	while (spec->precision_print-- > 0)
		if (spec->precision_print >= 0)
			write(1, "0", 1);
	ft_putnbr_base(num, "0123456789abcdef", spec);
}

void	print_nbr_minus_ptr(t_form *spec, unsigned long long num)
{
	char	fill;
	int		tmp;

	fill = ' ';
	tmp = spec->precision_print;
	write(1, "0x", 2);
	spec->printed += 2;
	while (tmp-- > 0)
		write(1, "0", 1);
	ft_putnbr_base(num, "0123456789abcdef", spec);
	while (spec->field_print-- > 0 && spec->field != 0)
		if (spec->precision_print >= 0 || spec->precision <= spec->field)
			write(1, &fill, 1);
}
