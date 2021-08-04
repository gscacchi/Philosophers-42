NAME	=	philosophers

SRCS	=	philosophers.c \
			routines.c \
			death.c \
			time.c \
			utils.c \

OBJS	=	$(SRCS:.c=.o)

%.o 	:	%.c
			$(CC) -Wall -Wextra -Werror -c $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@gcc -lpthread -pthread -Wall -Wextra -Werror -O3 -o $(NAME) $(OBJS)

clean	:	
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

run		:	$(NAME)
			./$(NAME) 4 410 200 200

.PHONY	:	all	clean fclean re run