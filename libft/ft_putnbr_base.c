/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:15:50 by lzaccome          #+#    #+#             */
/*   Updated: 2021/09/17 01:49:12 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_base(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

void	ft_putnbr_base(unsigned long nbr, char *base, t_form *spec)
{
	unsigned int	base_len;

	base_len = len_base(base);
	if (wrong_value(base, base_len) == 0)
		return ;
	if (nbr < base_len)
	{
		ft_putchar(base[nbr]);
		spec->printed++;
	}
	else
	{
		ft_putnbr_base((nbr / base_len), base, spec);
		ft_putnbr_base((nbr % base_len), base, spec);
	}
}
