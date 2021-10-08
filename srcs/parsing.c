/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:07:26 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/06 01:55:14 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	parsing(const char *src, va_list *my_list, t_form *spec)
{
	if (src[spec->i] == '-' || src[spec->i] == '0' || src[spec->i] == '+'
		|| src[spec->i] == ' ' || src[spec->i] == '#')
	{
		if (src[spec->i] == '-')
			spec->minus = 1;
		else if (src[spec->i] == '0')
			spec->zero = 1;
		else if (src[spec->i] == '+')
			spec->more = 1;
		else if (src[spec->i] == ' ')
			spec->space = 1;
		else if (src[spec->i] == '#')
			spec->sharp = 1;
		while (src[spec->i] == '-' || src[spec->i] == '#'
			|| src[spec->i] == '+' || src[spec->i] == ' ')
			spec->i++;
		while (src[spec->i] == '0' || src[spec->i] == '#'
			|| src[spec->i] == '+' || src[spec->i] == ' ')
			spec->i++;
	}
	parsing1(src, my_list, spec);
}

void	parsing1(const char *src, va_list *my_list, t_form *spec)
{
	if ((src[spec->i] >= '0' && src[spec->i] <= '9') || src[spec->i] == '*')
	{
		if (src[spec->i] == '*')
			spec->field = va_arg(*my_list, int);
		else
			spec->field = atoi(&src[spec->i]);
		if (spec->field < 0)
		{
			spec->field = -(spec->field);
			spec->minus = 1;
		}
	}
	parsing2(src, my_list, spec);
}

void	parsing2(const char *src, va_list *my_list, t_form *spec)
{
	while ((src[spec->i] >= '0' && src[spec->i] <= '9') || src[spec->i] == '*')
		spec->i++;
	if (src[spec->i] == '.')
	{
		spec->point = 1;
		spec->i++;
		if (src[spec->i] == '*')
			spec->precision = va_arg(*my_list, int);
		else
			spec->precision = atoi(&src[spec->i]);
	}
	while ((src[spec->i] >= '0' && src[spec->i] <= '9') || src[spec->i] == '*')
		spec->i++;
	if (src[spec->i] == 'c' || src[spec->i] == 'd' || src[spec->i] == 's'
		|| src[spec->i] == 'x' || src[spec->i] == 'X' || src[spec->i] == 'u'
		|| src[spec->i] == 'i' || src[spec->i] == 'p')
		spec->format = src[spec->i];
}
