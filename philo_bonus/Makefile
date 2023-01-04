NAME := philo_bonus
SRCS := philo_bonus.c ../philo/log.c ../philo/log2.c ../philo/helpers.c ../philo/helpers2.c work_bonus.c ../philo/work2.c init_bonus.c control_bonus.c state_bonus.c ../philo/ft_atoi_err.c
CFLAGS = -Wall -Wextra -Werror -O2 -DBONUS

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all