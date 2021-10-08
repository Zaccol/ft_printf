/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_filler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 00:57:19 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/04 02:35:16 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	fill_spec(t_form *spec, const char	*src)
{
	spec->minus = 0;
	spec->zero = 0;
	spec->field = 0;
	spec->precision = 0;
	spec->field_print = 0;
	spec->precision_print = 0;
	spec->point = 0;
	spec->value = 0;
	spec->i = 0;
	spec->printed = 0;
	spec->src = src;
	spec->p_case = 0;
	spec->more = 0;
	spec->sharp = 0;
	spec->space = 0;
}

void	reset_spec(t_form *spec)
{
	spec->minus = 0;
	spec->zero = 0;
	spec->field = 0;
	spec->precision = 0;
	spec->point = 0;
	spec->format = 0;
	spec->p_case = 0;
	spec->field_print = 0;
	spec->precision_print = 0;
	spec->more = 0;
	spec->sharp = 0;
	spec->space = 0;
}

void	printed_count(t_form *spec)
{
	if (spec->field_print < 0)
		spec->field_print = 0;
	if (spec->precision_print < 0)
		spec->precision_print = 0;
	spec->printed += spec->field_print + spec->precision_print;
}
