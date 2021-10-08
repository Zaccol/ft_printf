/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intlen_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:18:55 by lzaccome          #+#    #+#             */
/*   Updated: 2021/09/17 01:55:03 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_base2(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

int	intlen_base(unsigned long long int nbr, char *base, int intlen)
{
	unsigned long long int	base_len;

	base_len = len_base2(base);
	if (nbr < base_len)
		intlen++;
	else
	{
		intlen = intlen_base((nbr / base_len), base, intlen);
		intlen = intlen_base((nbr % base_len), base, intlen);
	}
	return (intlen);
}
