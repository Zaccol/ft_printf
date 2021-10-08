/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intlen_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:59:41 by lzaccome          #+#    #+#             */
/*   Updated: 2021/09/17 01:56:36 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	intlen_unsigned(unsigned int num)
{
	int	i;

	i = 0;
	while (num >= 1)
	{
		num = num / 10;
		i++;
	}
	return (i);
}
