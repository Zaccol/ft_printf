/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:07:26 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/12 23:19:04 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void    parsing(char *src, va_list *my_list, t_form *spec)
{
    if (src[spec->i] == '-' || src[spec->i] == '0')
    {
        if (src[spec->i] == '-')
            spec->minus = 1;
        else
            spec->zero =1;
        while (src[spec->i] == '-')
            spec->i++;
        while (src[spec->i] == '0')
            spec->i++;
    }
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
    if (src[spec->i] == 'c' || src[spec->i] == 'd' || src[spec->i] == 's' || src[spec->i] == 'x' || src[spec->i] == 'X' || src[spec->i] == 'u' || src[spec->i] == 'i' || src[spec->i] == 'p')
        spec->format = src[spec->i];
}