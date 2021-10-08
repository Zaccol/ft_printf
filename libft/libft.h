/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 05:01:33 by mleam             #+#    #+#             */
/*   Updated: 2021/10/05 06:04:30 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_form
{
	int			minus;
	int			zero;
	int			field;
	int			precision;
	int			field_print;
	int			precision_print;
	int			point;
	int			value;
	char		format;
	int			i;
	const char	*src;
	int			printed;
	int			p_case;
	int			more;
	int			sharp;
	int			space;
}	t_form;

int				len_base(char *base);
int				ft_atoi(const char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(char c);
void			ft_putnbr_base(unsigned long nbr, char *base, t_form *spec);
void			ft_putnbr_fd(int n, int fd);
int				intlen_base(unsigned long long int nbr, char *base, int intlen);
int				intlen_unsigned(unsigned int num);
int				intlen(long num);
size_t			ft_strlen(const char *s);
unsigned int	unsigned_nbr(unsigned int nbr);
int				wrong_value(char *base, int base_len);

#endif