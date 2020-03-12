/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:53:07 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/12 23:16:53 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void    print_nbr_standard(t_form *spec, int negnum, unsigned int num)
{
    char fill;

    fill = ' ';
    if (spec->zero == 1 && spec->precision == 0) // (sortir fill = 0 et le mettre au dessus) NON!
        fill = '0';
    if (negnum == 1 && spec->precision == 0)
        write (1, "-", 1);
    while (spec->field_print-- > 0 && spec->field != 0)
        write(1, &fill, 1);
    if (negnum == 1 && spec->precision != 0)
        write (1, "-", 1);
    while (spec->precision_print-- > 0)
        if (spec->precision_print >= 0)  // dans le cas ou le num est plus grand que le precision, n'affiche pas la largeur de champ
            write(1, "0", 1);
    if (spec->format == 'd' || spec->format == 'i' || spec->format == 'u') // mettre dans une fonction a part
        ft_putnbr_base(num, "0123456789");
    if (spec->format == 'x')
        ft_putnbr_base(num, "0123456789abcdef");
    if (spec->format == 'X')
        ft_putnbr_base(num, "0123456789ABCDEF");
}

void    print_nbr_minus(t_form *spec, int negnum, unsigned int num)
{
    char fill;
    int tmp;

    fill = ' ';
    tmp = spec->precision_print;
    if (negnum == 1)
        write (1, "-", 1);
    while (tmp-- > 0)
        write(1, "0", 1);
    if (spec->format == 'd' || spec->format == 'i' || spec->format == 'u')
        ft_putnbr_base(num, "0123456789");
    if (spec->format == 'x')
        ft_putnbr_base(num, "0123456789abcdef");
    if (spec->format == 'X')
        ft_putnbr_base(num, "0123456789ABCDEF");
    while (spec->field_print-- > 0 && spec->field != 0)
        if (spec->precision_print >= 0 || spec->precision <= spec->field)                   // dans le cas ou le num est plus grand que le precision, n'affiche pas la largeur de champ
            write(1, &fill, 1);
}

void    print_nbr_standard_ptr(t_form *spec, unsigned long long num)
{
    char fill;

    fill = ' ';
    if (spec->zero == 1 && spec->precision == 0) // (sortir fill = 0 et le mettre au dessus) NON!
        fill = '0';
    while (spec->field_print-- > 0 && spec->field != 0)
        write(1, &fill, 1);
    while (spec->precision_print-- > 0)
        if (spec->precision_print >= 0)  // dans le cas ou le num est plus grand que le precision, n'affiche pas la largeur de champ
            write(1, "0", 1);
    write(1, "0x", 2);
    ft_putnbr_base(num, "0123456789abcdef");
}

void    print_nbr_minus_ptr(t_form *spec, unsigned long long num)
{
    char fill;
    int tmp;

    fill = ' ';
    tmp = spec->precision_print;
    while (tmp-- > 0)
        write(1, "0", 1);
    write(1, "0x", 2);
    ft_putnbr_base(num, "0123456789abcdef");
    while (spec->field_print-- > 0 && spec->field != 0)
        if (spec->precision_print >= 0 || spec->precision <= spec->field)                   // dans le cas ou le num est plus grand que le precision, n'affiche pas la largeur de champ
            write(1, &fill, 1);
}