NAME = libft.a

SRCS = ft_atoi.o \
	   ft_putchar_fd.o \
	   ft_putchar.o \
	   ft_putnbr_base.o \
	   ft_putnbr_fd.o \
	   intlen_base.o \
	   intlen_unsigned.o\
	   intlen.o \
	   ft_strlen.o \
	   wrong_value.o



CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

$(NAME):	$(SRCS)
			ar rcs $(NAME) $(SRCS)

all:		$(NAME)

clean:
			$(RM) $(SRCS)

fclean:		clean
			$(RM) $(NAME)

re:
			fclean all


.PHONY:
			all clean fclean re
