/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:53:32 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/11 19:41:37 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

// int main()
// {
//     // char tab[6] = "Dag";
//     // char *ptr = tab;
//     int age = -567;
//     // char *src = "%0006.4s fsfsdfsdfs%d gfdgd";
//     // int i = 1;
    
//     // write(1, ptr, 6);
//     printf("%*.*d", 12, 5, age);
//     // printf("%d", atoi(&src[i]));
//     return (0);
// }

/*
- Conversion
'c'         The first byte of argument is printed.
Formats : %-"nbr"c / %*c
's'         Bytes from the string argument are printed until the end is reached or until the number of bytes indicated by the precision specification is reached; however if the precision is 0 or missing, the string is printed entirely.
'p'         The void * pointer argument is printed in hexadecimal (as if by `%#x' or `%#lx').
'd'/'i'/'u'/'x'/'X'       The int (or appropriate variant) argument is converted to signed decimal (d and i), unsigned decimal (u), or unsigned hexadecimal (x and X) notation.  The letters ``abcdef'' are used for x conversions; the letters ``ABCDEF'' are used for X conversions.  The precision, if any, gives the minimum
            number of digits that must appear; if the converted value requires fewer digits, it is padded on the left with zeros.
'%'         A `%' is written.  No argument is converted.  The complete conversion specification is `%%'.
    - Format
'0'         Zero padding.  For all conversions except n, the converted value is padded on the left with zeros rather than blanks.  If a precision is given with a numeric conversion (d, i, u, i, x, and X), the 0 flag is ignored.
%0"(nbr)"(d, u, i, x, X)
'-'         A minus sign `-' which specifies left adjustment of the output in the indicated field;
%-"(nbr)"(d, u, i, x, X, s, c, p)
'.'         An optional period, `.', followed by an optional digit string giving a precision which specifies the number of digits to appear after the decimal point, for e and f formats, or the maximum number of bytes to be printed from a string; if the digit string is missing, the precision is treated as zero;
%."(nbr)"(d, u, i, x, X, s)
%.p
'*'         Si la spécification de la largeur est un astérisque (*), un argument int issu de la liste d’arguments fournit la valeur. L’argument width doit précéder la valeur mise en forme dans la liste des arguments, comme illustré dans l’exemple suivant :
printf("%0*d", 5, 3); 00003 is output
Une valeur width manquante ou petite dans une spécification de conversion n’entraîne pas la troncation d’une valeur de sortie. Si le résultat d’une conversion est plus large que la valeur width, le champ peut être développé pour contenir le résultat de la conversion.
%*(d, i, u, x, X, s, c, p)
%0*(d, i, u, x, X, c)
%.*(d, i, u, x, X, s)
%-*(d, u, i, x, X, s, c, p)
*/

typedef struct s_form
{
    int minus;
    int zero;
    int field;
    int precision;
    int point;
    int value;
    char format;
} t_form;

void  fill_spec(t_form *spec)
{
    spec->minus = 0;
    spec->zero = 0;
    spec->precision = 0;
    spec->field = 0;
    spec->point = 0;
}

t_form    parsing(int i, char *src, ...)
{
    va_list my_list;
    t_form spec;
    // (void)i;
    // (void)src;
    fill_spec(&spec);
    va_start(my_list, src);

    if (src[i] == '-' || src[i] == '0')
    {
        if (src[i] == '-')
            spec.minus = 1;
        else
            spec.zero = 1;
        while (src[i] == '-')
            i++;
        while (src[i] == '0')
            i++;
    }
    if ((src[i] >= '0' && src[i] <= '9') || src[i] == '*')
    {
        if (src[i] == '*')
            spec.field = va_arg(my_list, int);
        else
            spec.field = atoi(&src[i]);
    }
    while ((src[i] >= '0' && src[i] <= '9') || src[i] == '*')
        i++;
    if (src[i] == '.')
    {
        spec.point = 1;
        i++;
        if (src[i] == '*')
            spec.precision = va_arg(my_list, int);
        else
            spec.precision = atoi(&src[i]);
    }
    while ((src[i] >= '0' && src[i] <= '9') || src[i] == '*')
        i++;
    if (src[i] == 'c' || src[i] == 'd' || src[i] == 's' || src[i] == 'x' || src[i] == 'X' || src[i] == 'u' || src[i] == 'i')
        spec.format = src[i];
    return (spec);
}

// int intlen(int num)
// {
//     int i;
//     i = 0;

//     if (num < 0)
//         num = -num;
//     while (num >= 1)
//     {
//         num = num/10;
//         i++;
//     }
//     return (i);
// }

int main()
{
    t_form spec;
    char *src = "%u yeah\n";

    spec = parsing(1, src);
    printf("MINUS : %d\nZERO : %d\nFIELD : %d\nPRECISION : %d\nVALUE : %d\nFORMAT : %c\nPOINT : %d\n", spec.minus, spec.zero, spec.field, spec.precision, spec.value, spec.format, spec.point);
    printf("printf :%04.7d", 6);   
}

// int main()
// {
//     unsigned int i;
//     i = -1;
//     char *src = "fuck";
//     // char *src = "hamster";

//     printf("%u\n%u\n%u\n%u\n%u", i+1, i, i-1, i-2, i-3);
//     // printf("i je m'appelle %s.%c lvl %-50.*i yeah\n\n", "Louis", 'Z', 30, -10);
//     // printf("d je m'appelle %s.%c lvl %-50.*d yeah\n\n", "Louis", 'Z', 3, i);
//     // printf("u je m'appelle %s.%c lvl %-50.*u yeah\n\n", "Louis", 'Z', 30, -10);
//     // printf("x je m'appelle %s.%c lvl %-.*x yeah\n\n", "Louis", 'Z', 3, -72);
//     // printf("X je m'appelle %s.%c lvl %-50.*X yeah\n\n", "Louis", 'Z', 0, -10);
//     // printf("p je m'appelle %s.%c lvl %-50p yeah\n\n", "Louis", 'Z', src);
// }

// int				wrong_value(char *base, int base_len)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 1;
// 	if (base_len <= 1)
// 		return (0);
// 	while (i <= base_len)
// 	{
// 		while (j <= base_len)
// 		{
// 			if ((base[i] == base[j]) || (base[i] == '-') || (base[i] == '+'))
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 		j = i + 1;
// 	}
// 	return (1);
// }

// void			ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// int				len_base(char *base)
// {
// 	int i;

// 	i = 0;
// 	while (base[i])
// 		i++;
// 	return (i);
// }

// unsigned int	unsigned_nbr(int nbr)
// {
// 	if (nbr < 0)
// 	{
// 		ft_putchar('-');
// 		return (nbr * -1);
// 	}
// 	return (nbr * 1);
// }

// void			ft_putnbr_base(int nbr, char *base)
// {
// 	unsigned int base_len;
// 	unsigned int nbr_uns;

// 	base_len = len_base(base);
// 	if (wrong_value(base, base_len) == 0)
// 		return ;
// 	nbr_uns = unsigned_nbr(nbr);
// 	if (nbr_uns < base_len)
// 		ft_putchar(base[nbr_uns]);
// 	else
// 	{
// 		ft_putnbr_base((nbr_uns / base_len), base);
// 		ft_putnbr_base((nbr_uns % base_len), base);
// 	}
// }

// int main()
// {
//     int i = -72;
//     char *base1 = "0123456789";
//     char *base;
//     char c = 'x';

//     if (c == 'x')
//         base = base1;
//     ft_putnbr_base(i, base);
// }