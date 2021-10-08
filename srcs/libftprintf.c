/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:24:01 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/06 20:07:39 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		g_tab_index[9] =
{
	's',
	'c',
	'd',
	'i',
	'x',
	'X',
	'u',
	'p',
	0
};

void			(*g_abFunction[8])(va_list *, t_form *) =
{
	my_printf_str,
	my_printf_char,
	my_printf_nbr,
	my_printf_nbr,
	my_printf_hexa,
	my_printf_hexa,
	my_printf_unsigned,
	my_printf_ptr
};

int	find_index(char *tab, char element)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		if (tab[i] == element)
			return (i);
		i++;
	}
	return (-1);
}

int	printf_percent(int percent, const char *src, t_form *spec)
{
	if (src[spec->i] == '%')
		percent++;
	else if (src[spec->i - 1] != '%' && is_format(src, spec))
		percent = 0;
	return (percent);
}

void	write_printf(const char *src, t_form *spec)
{
	write(1, &src[spec->i], 1);
	spec->printed++;
}

int	is_format(const char *src, t_form *spec)
{
	if ((src[spec->i] >= '0' && src[spec->i] <= '9') || src[spec->i] == '-'
		|| src[spec->i] == '*' || src[spec->i] == '.' || src[spec->i]
		== 'c' || src[spec->i] == 's' || src[spec->i] == 'p'
		|| src[spec->i] == 'd' || src[spec->i] == 'i' || src[spec->i] == 'u'
		|| src[spec->i] == 'x' || src[spec->i] == 'X' || src[spec->i] == '+'
		|| src[spec->i] == ' ' || src[spec->i] == '#')
		return (1);
	return (0);
}

int	ft_printf(const char *src, ...)
{
	va_list	my_list;
	t_form	spec;
	int		tmp_index;
	int		percent;

	tmp_index = 0;
	va_start(my_list, src);
	fill_spec(&spec, src);
	while (src[spec.i] != 0)
	{
		percent = printf_percent(percent, src, &spec);
		if (condition(src, &spec, percent))
		{
			parsing(src, &my_list, &spec);
			tmp_index = find_index(g_tab_index, src[spec.i]);
			if (tmp_index != -1)
				(*g_abFunction[tmp_index])(&my_list, &spec);
			reset_spec(&spec);
			percent = 0;
		}
		else if (src[spec.i] != '%' || (percent % 2) == 0)
			write_printf(src, &spec);
		spec.i++;
	}
	return (spec.printed);
}
