# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 15:37:56 by lzaccome          #+#    #+#              #
#    Updated: 2021/09/30 22:58:57 by lzaccome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

SRCS_D =	srcs/

OBJS_N =	libftprintf.o \
			display.o \
			parsing.o \
			ft_printing1.o \
			ft_printing2.o \
			spec_filler.o

OBJS_P =	$(addprefix $(SRCS_D), $(OBJS_N))

LIBFT_D =	libft/

SRCS =		ft_atoi.o \
		   	ft_isspace.o \
			ft_putchar_fd.o \
			ft_putchar.o \
			ft_putnbr_base.o\
			ft_putnbr_fd.o\
			intlen_base.o\
			intlen_unsigned.o\
			intlen.o\
			ft_strlen.o\
			unsigned_nbr.o\
			wrong_value.o

LIBFT_P = $(addprefix $(LIBFT_D), $(LIBFT_N))

INCS	= -I includes/

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

$(NAME):	$(OBJS_P) $(LIBFT_P)
			make -C $(LIBFT_D)
			cp libft/libft.a $(NAME)
			ar -rcs $(NAME) $(OBJS_P)

all:		$(NAME)

bonus:		all

clean:
			$(MAKE) clean -C $(LIBFT_D)
			rm -f $(OBJS_P)

fclean:		clean
			$(MAKE) fclean -C $(LIBFT_D)
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
