NAME = philo
GCC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c \
		utils.c \
		init.c \
		operations.c \

OBJS = $(SRCS:.c=.o)

INCLUDES = philo.h

# Правило, если нет объектного файла соответсвующего сишному файлу или сишный файл изменился - скомпилирует объктный файл
%.o: %.c
	gcc $(FLAGS) -c $< -o $@ -I$(INCLUDES) 

# Если объектный файл или библиотека изменилась, перекомпилирует выходной файл
$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(basename $(NAME))

all:  $(NAME)

# $(NAME): $(OBJS) philo.h Makefile
# 	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME) - при тач пересобирается, неверно

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
