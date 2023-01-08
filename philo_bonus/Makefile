NAME := philo_bonus
SRCS := philo_bonus.c ../philo/log.c ../philo/log2.c ../philo/helpers.c ../philo/helpers2.c ../philo/death.c ../philo/work.c init_bonus.c control_bonus.c fork_bonus.c ../philo/ft_atoi_err.c
CFLAGS = -Wall -Wextra -Werror -O2 -pthread -DBONUS

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all