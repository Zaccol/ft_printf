/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:54:38 by lzaccome          #+#    #+#             */
/*   Updated: 2020/03/12 22:26:28 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long int		lli;

	lli = n;
	if (lli < 0)
	{
		ft_putchar_fd('-', fd);
		lli = -lli;
	}
	if (lli > 9)
	{
		ft_putnbr_fd(lli / 10, fd);
		ft_putchar_fd((lli % 10) + '0', fd);
	}
	else
	{
		ft_putchar_fd(lli + '0', fd);
	}
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* ATOI start */

static int	ft_isspace(const char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && (*str < ':' && *str > '/'))
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}

/* ATOI end */

int intlen(int num)
{
    int i;
    i = 0;

	if (num < 0)
        num = -num;
    while (num >= 1)
    {
        num = num/10;
        i++;
    }
    return (i);
}

int intlen_unsigned(unsigned int num)
{
    int i;
    i = 0;

	if (num < 0)
        num = -num;
    while (num >= 1)
    {
        num = num/10;
        i++;
    }
    return (i);
}

int			intlen_base(unsigned int nbr, char *base, int intlen)
{
	unsigned int base_len;

	base_len = len_base(base);
	if (nbr < base_len)
        intlen++;
	else
	{
		intlen = intlen_base((nbr / base_len), base, intlen);
		intlen = intlen_base((nbr % base_len), base, intlen);
	}
    return(intlen);
}

// BASE

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

void			ft_putnbr_base(unsigned long nbr, char *base)
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

// BASE end