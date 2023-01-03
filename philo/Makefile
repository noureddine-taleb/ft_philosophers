NAME := philo
SRCS := philo.c log.c log2.c helpers.c helpers2.c work.c work2.c init.c state.c control.c ft_atoi_err.c
CFLAGS = -Wall -Wextra -Werror -pthread -O2

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all