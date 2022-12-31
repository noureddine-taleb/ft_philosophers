NAME := philo
SRCS := philo.c log.c log2.c helpers.c work.c work2.c init.c state.c ft_atoi_err.c
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all