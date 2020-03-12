INC		=	libftprintf.h
NAME	=	libftprintf.a
SRC		=	libftprintf.c\
			parsing.c\
			utils.c\
			display.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Werror -Wextra -c
CC		= 	gcc
AR		=	ar rc
all:		$(NAME)
$(NAME):	$(OBJ) $(INC)
			$(AR) $(NAME) $(OBJ)
%.o:		%.c
			$(CC) $(CFLAGS) $<
clean:
			rm -f $(OBJ)
fclean:		clean
			rm -f $(NAME)
re:			fclean all
.PHONY:		all clean fclean