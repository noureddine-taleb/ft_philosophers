NAME := philo
SRCS := philo.c log.c ft_atoi_err.c
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all