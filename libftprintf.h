/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:38:23 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/12 23:17:06 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_form
{
    int minus;
    int zero;
    int field;
    int precision;
    int field_print;
    int precision_print;
    int point;
    int value; // potentielement supprimable
    char format;
    int i;
    char *src;
    int printed;
} t_form;

void    my_printf_str(va_list *my_list, t_form *spec);
void    my_printf_char(va_list *my_list, t_form *spec);
void    my_printf_nbr(va_list *my_list, t_form *spec);
int     findIndex(char *tab, char element);
t_form    ft_printf(char *src, ...);
int     main(int ac, char const **argv);
void     ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
// static int	ft_isspace(const char c);
int		ft_atoi(const char *str);
void printf_parsing1(int i, char *src);
void    printf_precision(int i, char *src, int size_flag);
void    parsing(char *src, va_list *my_list, t_form *spec);
void    fill_spec(t_form *spec, char *src);
int     intlen(int num);
void    reset_spec(t_form *spec);
void    print_nbr_standard(t_form *spec, int negnum, unsigned int num);
void    print_nbr_minus(t_form *spec, int negnum, unsigned int num);
void    my_printf_hexa(va_list *my_list, t_form *spec);
void	ft_putnbr_base(unsigned long nbr, char *base);
unsigned int	unsigned_nbr(unsigned int nbr);
int				len_base(char *base);
int				wrong_value(char *base, int base_len);
void			ft_putchar(char c);
void    print_nbr_hexa(t_form *spec, int negnum, unsigned int num);
void    my_printf_unsigned(va_list *my_list, t_form *spec);
int     intlen_unsigned(unsigned int num);
int			intlen_base(unsigned int nbr, char *base, int intlen);
void    my_printf_ptr(va_list *my_list, t_form *spec);
void    print_nbr_standard_ptr(t_form *spec, unsigned long long num);
void    print_nbr_minus_ptr(t_form *spec, unsigned long long num);

#endif