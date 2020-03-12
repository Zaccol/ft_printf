/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:24:01 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/12 23:16:52 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void  fill_spec(t_form *spec, char *src)
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
}

void reset_spec(t_form *spec)
{
    spec->minus = 0;
    spec->zero = 0;
    spec->field = 0;
    spec->precision = 0;
    spec->point = 0;
    spec->format = 0;
}

void    my_printf_str(va_list *my_list, t_form *spec)
{
    char *src = va_arg(*my_list, char *);
    int field_print;
    int precision_print;
    // int negnum;
    int srclen;

    srclen = strlen(src);
    // negnum = 0; 
    if (spec->precision < srclen && spec->point == 1)
        precision_print = spec->precision;
    else
        precision_print = srclen;
    field_print = spec->field - precision_print;
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

void    my_printf_char(va_list *my_list, t_form *spec)
{
    char c = va_arg(*my_list, int);
    int field_print;

    field_print = spec->field - 1; 
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

void    my_printf_nbr(va_list *my_list, t_form *spec)
{
    int num = va_arg(*my_list, int);
    if (spec->format == 'u')
    {
        num = 4294967296 - (num * -1);
        printf("%u", num);
    }
    int numlen;
    int negnum;

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
    if (num < 0)
    {
        num = -num;
        spec->field_print--;
        negnum = 1;
    }
    if (spec->minus == 0)
        print_nbr_standard(spec, negnum, num);
    if (spec->minus == 1)
        print_nbr_minus(spec, negnum, num);
}

void    my_printf_unsigned(va_list *my_list, t_form *spec)
{
    unsigned int num = va_arg(*my_list, unsigned int);
    num = 4294967296 - (num * -1);
    int numlen;
    int negnum;

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
    if (spec->minus == 0)
        print_nbr_standard(spec, negnum, num);
    if (spec->minus == 1)
        print_nbr_minus(spec, negnum, num);
}

void    my_printf_hexa(va_list *my_list, t_form *spec)
{
    unsigned int num = va_arg(*my_list, unsigned int);
    int numlen;
    int negnum;

    negnum = 0;
    if (num == 0)
        numlen = 1;
    else
    {
        numlen = intlen_base(num, "0123456789abcdef", 0);
        // printf("\n%d\n", numlen);
    }
    if (spec->precision > numlen)
        spec->field_print = spec->field - spec->precision;
    else
        spec->field_print = spec->field - numlen;
    spec->precision_print = spec->precision - numlen;
    if (num < 0)
    {
        num = -num;
        spec->field_print--;
        negnum = 1;
    }
    if (spec->minus == 0)
        print_nbr_standard(spec, negnum, num);
    if (spec->minus == 1)
        print_nbr_minus(spec, negnum, num);
}

void    my_printf_ptr(va_list *my_list, t_form *spec)
{
    unsigned long long num = va_arg(*my_list, unsigned long long);
    int numlen;

    if (num == 0)
        numlen = 1;
    else
    {
        numlen = (intlen_base(num, "0123456789abcdef", 0) + 4);
        // printf("\n%d\n", numlen);
    }
    if (spec->precision > numlen)
        spec->field_print = spec->field - spec->precision;
    else
        spec->field_print = spec->field - numlen;
    spec->precision_print = spec->precision - numlen;
    // if (num < 0)
    // {
    //     num = -num;
    //     spec->field_print--;
    //     negnum = 1;
    // }
    if (spec->minus == 0)
        print_nbr_standard_ptr(spec, num);
    if (spec->minus == 1)
        print_nbr_minus_ptr(spec, num);
}

int findIndex(char *tab, char element)
{
    int i = 0;

    while (tab[i] != 0)
    {
        if (tab[i] == element)
            return (i);
        i++;
    }
    return (-1);
}

t_form  ft_printf(char *src, ...)
{
    void (*tabFunction[7]) (va_list *, t_form *) = {my_printf_str, my_printf_char, my_printf_nbr, my_printf_nbr, my_printf_hexa, my_printf_unsigned, my_printf_ptr};
    char tabIndex[8] = {'s', 'c', 'd', 'i', 'x', 'u', 'p', 0};
    va_list my_list;
    t_form spec;
    fill_spec(&spec, src);
    int tmpIndex = 0;

    va_start(my_list, src);
    while (src[spec.i] != 0)
    {
        if (spec.i != 0 && src[spec.i - 1] == '%')
        {
            if ((src[spec.i] >= '0' && src[spec.i] <= '9') || src[spec.i] == '-' || src[spec.i] == '*' || src[spec.i] == '.' 
            || src[spec.i] == 'c' || src[spec.i] == 's' || src[spec.i] == 'p' || src[spec.i] == 'd' || src[spec.i] == 'i'
            || src[spec.i] == 'u' || src[spec.i] == 'x' || src[spec.i] == 'X')
            {
                parsing(src, &my_list, &spec);
                // spec.i++;
            }
            tmpIndex = findIndex(tabIndex, src[spec.i]);
            if (tmpIndex != -1)
                (*tabFunction[tmpIndex]) (&my_list, &spec);
            reset_spec(&spec);
        }
        else if (src[spec.i] != '%')
        {
            write(1, &src[spec.i], 1);
        }
        spec.i++;
    }
    // va_end(my_list);
    return (spec);
}

int main(int ac, char const **argv)
{
    (void)ac;
    (void)argv;
    t_form spec;

    spec = ft_printf("1 je m'appelle %s.%c lvl %-*d yeah\n", "Louis", 'Z', 6, 00111); // tester avec des 0 devant le num
    printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nI : %d\nSRC : %s\nprinted : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.i, spec.src, spec.printed);
    printf("1 je m'appelle %s.%c lvl %-*d yeah\n\n", "Louis", 'Z', 6, 00111);

    spec = ft_printf("2 je m'appelle %s.%c lvl %-*.*d yeah\n", "Louis", 'Z', 6, 4, 111);
    printf("2 je m'appelle %s.%c lvl %-*.*d yeah\n\n", "Louis", 'Z', 6, 4, 111);

    spec = ft_printf("3 je m'appelle %s.%c lvl %-*.*d yeah\n", "Louis", 'Z', 4, 6, 111);
    printf("3 je m'appelle %s.%c lvl %-*.*d yeah\n\n", "Louis", 'Z', 4, 6, 111);

    spec = ft_printf("4 je m'appelle %s.%c lvl %-.*d yeah\n", "Louis", 'Z', 6, 111);
    printf("4 je m'appelle %s.%c lvl %-.*d yeah\n\n", "Louis", 'Z', 6, 111);

    spec = ft_printf("5 je m'appelle %s.%c lvl %0*d yeah\n", "Louis", 'Z', 6, 111);
    printf("5 je m'appelle %s.%c lvl %0*d yeah\n\n", "Louis", 'Z', 6, 111);

    spec = ft_printf("6 je m'appelle %s.%c lvl %0*.*d yeah\n", "Louis", 'Z', 6, 4, 111);
    printf("6 je m'appelle %s.%c lvl %0*.*d yeah\n\n", "Louis", 'Z', 6, 4, 111);

    spec = ft_printf("7 je m'appelle %s.%c lvl %0*.*d yeah\n", "Louis", 'Z', 4, 6, 111);
    printf("7 je m'appelle %s.%c lvl %0*.*d yeah\n\n", "Louis", 'Z', 4, 6, 111);

    spec = ft_printf("8 je m'appelle %s.%c lvl %0.*d yeah\n", "Louis", 'Z', 6, 111);
    printf("8 je m'appelle %s.%c lvl %0.*d yeah\n\n", "Louis", 'Z', 6, 111);

    spec = ft_printf("9 je m'appelle %s.%c lvl %-*.*d yeah\n", "Louis", 'Z', 6, 4, -111);
    printf("9 je m'appelle %s.%c lvl %-*.*d yeah\n\n", "Louis", 'Z', 6, 4, -111);

    spec = ft_printf("10 je m'appelle %s.%c lvl %0*.*d yeah\n", "Louis", 'Z', 6, 4, -111);
    printf("10 je m'appelle %s.%c lvl %0*.*d yeah\n\n", "Louis", 'Z', 6, 4, -111);

    spec = ft_printf("11 je m'appelle %s.%c lvl %-*.*d yeah\n", "Louis", 'Z', 4, 6, -111);
    printf("11 je m'appelle %s.%c lvl %-*.*d yeah\n\n", "Louis", 'Z', 4, 6, -111);

    spec = ft_printf("12 je m'appelle %s.%c lvl %0*d yeah\n", "Louis", 'Z', 6, -111);
    printf("12 je m'appelle %s.%c lvl %0*d yeah\n\n", "Louis", 'Z', 6, -111);

    spec = ft_printf("13 je m'appelle %s.%c lvl %0.*d yeah\n", "Louis", 'Z', 6, -111);
    printf("13 je m'appelle %s.%c lvl %0.*d yeah\n\n", "Louis", 'Z', 6, -111);

    spec = ft_printf("14 je m'appelle %s.%c lvl %-.*d yeah\n", "Louis", 'Z', 6, -111);
    printf("14 je m'appelle %s.%c lvl %-.*d yeah\n\n", "Louis", 'Z', 6, -111);

    spec = ft_printf("15 je m'appelle %10s.%c lvl %-.*d yeah\n", "Louis", 'Z', 2, -111);
    printf("15 je m'appelle %10s.%c lvl %-.*d yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("16 je m'appelle %10.3s.%c lvl %0.*d yeah\n", "Louis", 'Z', 2, -111);
    printf("16 je m'appelle %10.3s.%c lvl %0.*d yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("17 je m'appelle %.3s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("17 je m'appelle %.3s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %3.10s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %3.10s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %50.1s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %50.1s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %1.50s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %1.50s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("15 je m'appelle %-10s.%c lvl %-.*d yeah\n", "Louis", 'Z', 2, -111);
    printf("15 je m'appelle %-10s.%c lvl %-.*d yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("16 je m'appelle %-10.3s.%c lvl %0.*d yeah\n", "Louis", 'Z', 2, -111);
    printf("16 je m'appelle %-10.3s.%c lvl %0.*d yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("17 je m'appelle %-.3s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("17 je m'appelle %-.3s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %-3.10s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %-3.10s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %-50.1s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %-50.1s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %-1.50s.%c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %-1.50s.%c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %.50s.%10c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %.50s.%10c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %s.%-10c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %s.%-10c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %10.50s.%1c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %10.50s.%1c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %10.50s.%5c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %10.50s.%5c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %.50s.%-1c lvl %.d yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %.50s.%-1c lvl %.d yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("%-6.4d yeah\n", -111);
    printf("%-6.4d yeah\n\n", -111);

    spec = ft_printf("je m'appelle %s.%c lvl %-10.*d yeah\n", "Louis", 'Z', 5, 0);
    printf("je m'appelle %s.%c lvl %-10.*d yeah\n\n", "Louis", 'Z', 5, 0);

    spec = ft_printf("%-6.4i yeah\n", -111);
    printf("%-6.4i yeah\n\n", -111);

    spec = ft_printf("je m'appelle %s.%c lvl %-10.*i yeah\n", "Louis", 'Z', 5, 0);
    printf("je m'appelle %s.%c lvl %-10.*i yeah\n\n", "Louis", 'Z', 5, 0);

    spec = ft_printf("my : je m'appelle %s.%c lvl %0d yeah\n", "Louis", 'Z', 2);
    // printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nI : %d\nSRC : %s\nprinted : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.i, spec.src, spec.printed);
    printf("of : je m'appelle %s.%c lvl %0d yeah\n\n", "Louis", 'Z', 2);

    spec = ft_printf("je m'appelle %s.%c lvl %-*d yeah\n", "Louis", 'Z', 5, 00111);
    printf("je m'appelle %s.%c lvl %-*d yeah\n\n", "Louis", 'Z', 5, 00111);

    spec = ft_printf("je m'appelle %s.%c lvl %-*x yeah\n", "Louis", 'Z', 5, 111);
    printf("je m'appelle %s.%c lvl %-*x yeah\n\n", "Louis", 'Z', 5, 111);

    // HEXA 

    spec = ft_printf("2 je m'appelle %s.%c lvl %-*.*x yeah\n", "Louis", 'Z', 6, 4, 111);
    printf("2 je m'appelle %s.%c lvl %-*.*x yeah\n\n", "Louis", 'Z', 6, 4, 111);

    spec = ft_printf("3 je m'appelle %s.%c lvl %-*.*x yeah\n", "Louis", 'Z', 4, 6, 111);
    printf("3 je m'appelle %s.%c lvl %-*.*x yeah\n\n", "Louis", 'Z', 4, 6, 111);

    spec = ft_printf("4 je m'appelle %s.%c lvl %-.*x yeah\n", "Louis", 'Z', 6, 111);
    printf("4 je m'appelle %s.%c lvl %-.*x yeah\n\n", "Louis", 'Z', 6, 111);

    spec = ft_printf("5 je m'appelle %s.%c lvl %0*x yeah\n", "Louis", 'Z', 6, 111);
    printf("5 je m'appelle %s.%c lvl %0*x yeah\n\n", "Louis", 'Z', 6, 111);

    spec = ft_printf("6 je m'appelle %s.%c lvl %0*.*x yeah\n", "Louis", 'Z', 6, 4, 111);
    printf("6 je m'appelle %s.%c lvl %0*.*x yeah\n\n", "Louis", 'Z', 6, 4, 111);

    spec = ft_printf("7 je m'appelle %s.%c lvl %0*.*x yeah\n", "Louis", 'Z', 4, 6, 111);
    printf("7 je m'appelle %s.%c lvl %0*.*x yeah\n\n", "Louis", 'Z', 4, 6, 111);

    spec = ft_printf("8 je m'appelle %s.%c lvl %0.*x yeah\n", "Louis", 'Z', 6, 111);
    printf("8 je m'appelle %s.%c lvl %0.*x yeah\n\n", "Louis", 'Z', 6, 111);

    spec = ft_printf("9 je m'appelle %s.%c lvl %-*.*x yeah\n", "Louis", 'Z', 6, 4, -111);
    printf("9 je m'appelle %s.%c lvl %-*.*x yeah\n\n", "Louis", 'Z', 6, 4, -111);

    spec = ft_printf("10 je m'appelle %s.%c lvl %0*.*x yeah\n", "Louis", 'Z', 6, 4, -111);
    printf("10 je m'appelle %s.%c lvl %0*.*x yeah\n\n", "Louis", 'Z', 6, 4, -111);

    spec = ft_printf("11 je m'appelle %s.%c lvl %-*.*x yeah\n", "Louis", 'Z', 4, 6, -111);
    printf("11 je m'appelle %s.%c lvl %-*.*x yeah\n\n", "Louis", 'Z', 4, 6, -111);

    spec = ft_printf("12 je m'appelle %s.%c lvl %0*x yeah\n", "Louis", 'Z', 6, -111);
    printf("12 je m'appelle %s.%c lvl %0*x yeah\n\n", "Louis", 'Z', 6, -111);

    spec = ft_printf("13 je m'appelle %s.%c lvl %0.*x yeah\n", "Louis", 'Z', 6, -111);
    printf("13 je m'appelle %s.%c lvl %0.*x yeah\n\n", "Louis", 'Z', 6, -111);

    spec = ft_printf("14 je m'appelle %s.%c lvl %-.*x yeah\n", "Louis", 'Z', 6, -111);
    printf("14 je m'appelle %s.%c lvl %-.*x yeah\n\n", "Louis", 'Z', 6, -111);

    spec = ft_printf("15 je m'appelle %10s.%c lvl %-.*x yeah\n", "Louis", 'Z', 2, -111);
    printf("15 je m'appelle %10s.%c lvl %-.*x yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("16 je m'appelle %10.3s.%c lvl %0.*x yeah\n", "Louis", 'Z', 2, -111);
    printf("16 je m'appelle %10.3s.%c lvl %0.*x yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("17 je m'appelle %.3s.%c lvl %.x yeah\n", "Louis", 'Z', -111);
    printf("17 je m'appelle %.3s.%c lvl %.x yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %3.10s.%c lvl %.x yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %3.10s.%c lvl %.x yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %50.1s.%c lvl %.x yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %50.1s.%c lvl %.x yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %1.50s.%c lvl %.x yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %1.50s.%c lvl %.x yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("16 je m'appelle %s.%c lvl %.x yeah\n", "Louis", 'Z', -111);
    printf("16 je m'appelle %s.%c lvl %.x yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("15 je m'appelle %-10s.%c lvl %-.*x yeah\n", "Louis", 'Z', 2, -111);
    printf("15 je m'appelle %-10s.%c lvl %-.*x yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("16 je m'appelle %-10.3s.%c lvl %0.*x yeah\n", "Louis", 'Z', 2, -111);
    // printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nI : %d\nSRC : %s\nprinted : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.i, spec.src, spec.printed);
    printf("16 je m'appelle %-10.3s.%c lvl %0.*x yeah\n\n", "Louis", 'Z', 2, -111);

    spec = ft_printf("je m'appelle %s.%c lvl %-*x yeah\n", "Louis", 'Z', 5, 111);
    // printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nI : %d\nSRC : %s\nprinted : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.i, spec.src, spec.printed);
    printf("je m'appelle %s.%c lvl %-*x yeah\n\n", "Louis", 'Z', 5, 111);

    spec = ft_printf("je m'appelle %s.%c lvl %05.4d yeah\n", "Louis", 'Z', 00111);
    // printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nI : %d\nSRC : %s\nprinted : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.i, spec.src, spec.printed);
    printf("je m'appelle %s.%c lvl %05.4d yeah\n\n", "Louis", 'Z', 00111);

    spec = ft_printf("je m'appelle %s.%c lvl %-25u yeah\n", "Louis", 'Z', -111);
    // printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nI : %d\nSRC : %s\nprinted : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.i, spec.src, spec.printed);
    printf("je m'appelle %s.%c lvl %-25u yeah\n\n", "Louis", 'Z', -111);

    spec = ft_printf("je m'appelle %s.%c lvl %-*.*x yeah\n", "Louis", 'Z', 7, 3, 111);
    printf("je m'appelle %s.%c lvl %-*.*x yeah\n\n", "Louis", 'Z', 7, 3, 111);

    spec = ft_printf("je m'appelle %s.%c lvl %-*p yeah\n", "Louis", 'Z', 30, "oui");
    printf("je m'appelle %s.%c lvl %-*p yeah\n\n", "Louis", 'Z', 30, "oui");

    spec = ft_printf("|%-*.*d| yeah\n", -3, -2, 4);
    printf("|%-*.*d| yeah\n\n", -3, -2, 4);

    spec = ft_printf("|%*d| yeah\n", -3, 4);
    printf("|%*d| yeah\n\n", -3, 4);

    spec = ft_printf("|%-*d| yeah\n", 3, 4);
    printf("|%-*d| yeah\n\n", 3, 4);

    spec = ft_printf("|%.*d| yeah\n", -5, 4);
    printf("|%.*d| yeah\n\n", -5, 4);

    spec = ft_printf("|%.0d| yeah\n", 0);
    printf("|%.0d| yeah\n", 0);
}