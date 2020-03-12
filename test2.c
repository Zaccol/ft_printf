/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:40:37 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/12 22:06:06 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// int main()
// {
//     int num;
//     int num2;

//     num = -1;
//     num2 = -2;

//     // num = (unsigned int)num;
//     printf("num : %u\n", num);
//     printf("num : %u\n", num2);
// }

// int				len_base(char *base)
// {
// 	int i;

// 	i = 0;
// 	while (base[i])
// 		i++;
// 	return (i);
// }

// int			intlen_base(unsigned int nbr, char *base, int intlen)
// {
// 	unsigned int base_len;

// 	base_len = len_base(base);
// 	if (nbr < base_len)
//         intlen++;
// 	else
// 	{
// 		intlen = intlen_base((nbr / base_len), base, intlen);
// 		intlen = intlen_base((nbr % base_len), base, intlen);
// 	}
//     return(intlen);
// }

// int main()
// {
//     int intlen;
//     intlen = intlen_base(535005646, "0123456789abcdef", 0);
//     printf("\nintlen : %d\n", intlen);
//     return(0);
// }

int				wrong_value(char *base, int base_len)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (base_len <= 1)
		return (0);
	while (i <= base_len)
	{
		while (j <= base_len)
		{
			if ((base[i] == base[j]) || (base[i] == '-') || (base[i] == '+'))
				return (0);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (1);
}

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

int				len_base(char *base)
{
	int i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

unsigned int	unsigned_nbr(unsigned int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		return (nbr * -1);
	}
	return (nbr * 1);
}

void			ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int base_len;
	// unsigned int nbr_uns;

	base_len = len_base(base);
	if (wrong_value(base, base_len) == 0)		//potentiellement inutile
		return ;
	// nbr_uns = unsigned_nbr(nbr);             Retransformer tous les nbr suivant en nbr_uns si probleme, normalement tous les num envoyé sont positifs
	if (nbr < base_len)
		ft_putchar(base[nbr]);
	else
	{
		ft_putnbr_base((nbr / base_len), base);
		ft_putnbr_base((nbr % base_len), base);
	}
}

int main()
{
    unsigned int ouais;

    write(1, "0x7ffe", 6);
    ft_putnbr_base(&ouais, "0123456789abcdef");
    printf("\n%p", &ouais);
    return(0);
}