NAME = philo 

CC = cc 

CFLAGS = -Wall -Wextra -Werror

SRC =	main.c\
		init.c\
		utils.c\
		operations.c\

OBJ = $(patsubst %.c, %.o, $(SRC))

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) philo.c
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
