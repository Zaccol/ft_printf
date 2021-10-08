/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:38:23 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/06 20:11:10 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"

void	my_printf_str(va_list *my_list, t_form *spec);
void	my_printf_char(va_list *my_list, t_form *spec);
void	my_printf_nbr(va_list *my_list, t_form *spec);
int		find_index(char *tab, char element);
int		ft_printf(const char *src, ...);
void	printf_parsing1(int i, char *src);
void	printf_precision(int i, char *src, int size_flag);
void	parsing(const char *src, va_list *my_list, t_form *spec);
void	parsing1(const char *src, va_list *my_list, t_form *spec);
void	parsing2(const char *src, va_list *my_list, t_form *spec);
void	fill_spec(t_form *spec, const char *src);
void	reset_spec(t_form *spec);
void	print_nbr_standard(t_form *spec, int negnum, unsigned int num);
void	print_nbr_minus(t_form *spec, int negnum, unsigned int num);
void	my_printf_hexa(va_list *my_list, t_form *spec);
void	ft_putchar(char c);
void	print_nbr_hexa(t_form *spec, int negnum, unsigned int num);
void	my_printf_unsigned(va_list *my_list, t_form *spec);
void	my_printf_ptr(va_list *my_list, t_form *spec);
void	print_nbr_standard_ptr(t_form *spec, unsigned long long num);
void	print_nbr_minus_ptr(t_form *spec, unsigned long long num);
void	printed_count(t_form *spec);
void	write_str(int precision_print, int field_print,
			t_form *spec, char *src);
long	fill_nbr(long num, int *negnum, t_form *spec);
int		is_format(const char *src, t_form *spec);
void	write_printf(const char *src, t_form *spec);
int		condition(const char *src, t_form *spec, int percent);

#endif