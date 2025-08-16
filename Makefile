CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -fsanitize=thread -g
NAME    = philo

SRC     = main.c valid_argument.c init_data.c utils.c create_threads.c get_time_ms.c print_error.c action.c check_dead.c small_atoi.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
