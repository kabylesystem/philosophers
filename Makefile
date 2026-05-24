NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
THREAD		= -pthread

SRCS		= main.c parsing.c init.c routine.c threads.c time.c utils.c
OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(THREAD) $(OBJS) -o $(NAME)

%.o:		%.c philo.h
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
