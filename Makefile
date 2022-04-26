NAME = philo
GCC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c \
		utils.c \
		init.c \
		operations.c \

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) philo.h Makefile
	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
