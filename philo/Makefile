NAME := philo
SRCS := philo.c log.c helpers.c work.c init.c ft_atoi_err.c
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all