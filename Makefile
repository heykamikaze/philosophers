NAME = philo

NAME_BONUS = philo_bonus

GCC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address

SRCS = main.c \
		utils.c \
		init.c \
		operations.c \
		process.c\

SRC_BONUS = check_args_bonus.c \
			get_time_bonus.c \
			init_bonus.c \
			life_cycle_bonus.c \
			main_bonus.c utils_bonus.c \
			life_cycle_utils_bonus.c\

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCLUDES = philo.h \
			philo_bonus.h \

# Правило, если нет объектного файла соответсвующего сишному файлу или сишный файл изменился - скомпилирует объктный файл
%.o: %.c
	gcc $(FLAGS) -c $< -o $@
# gcc $(FLAGS) -c $< -o $@ -I$(INCLUDES) 

# Если объектный файл или библиотека изменилась, перекомпилирует выходной файл
$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	gcc $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

all:  $(NAME)

# $(NAME): $(OBJS) philo.h Makefile
# 	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME) - при тач пересобирается, неверно

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean


# NAME = philo
# NAME_BONUS = philo_bonus

# CC = cc

# CFLAGS = -Wall -Wextra -Werror

# SRC = check_input.c creat_threads.c get_time.c init.c life_cycle_philo.c main.c utils.c
# SRC_BONUS = check_input_bonus.c get_time_bonus.c init_bonus.c life_cycle_philo_bonus.c main_bonus.c utils_bonus.c life_cycle_utils_bonus.c

# OBJ = $(patsubst %.c, %.o, $(SRC))
# OBJ_BONUS = $(patsubst %.c, %.o, $(SRC_BONUS))

# RM = rm -rf

# all: $(NAME)
