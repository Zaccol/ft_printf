/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:08:01 by lzaccome          #+#    #+#             */
/*   Updated: 2021/09/17 01:59:23 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wrong_value(char *base, int base_len)
{
	int	i;
	int	j;

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
