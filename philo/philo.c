/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/30 20:14:07 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

// TODO: leaks
#include "philo.h"

void msleep(int msec)
{
	usleep(msec * 1000);
}

void	help()
{
	printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	parse_args(char **argv, int argc, t_state *state)
{
	int	err;

	if (argc < 4)
		return (help(), -1);
	state->number_of_philosophers = ft_atoi_err(argv[0], (err = 0, &err));
	if (err || state->number_of_philosophers <= 1)
		return (printf("number of philosophers should be bigger than 1\n"), -1);
	state->time_to_die = ft_atoi_err(argv[1], (err = 0, &err));
	if (err || state->time_to_die <= 0)
		return (printf("time to die should be bigger than 0\n"), -1);
	state->time_to_eat = ft_atoi_err(argv[2], (err = 0, &err));
	if (err || state->time_to_eat <= 0)
		return (printf("time to eat should be bigger than 0\n"), -1);
	state->time_to_sleep = ft_atoi_err(argv[3], (err = 0, &err));
	if (err || state->time_to_sleep <= 0)
		return (printf("time to sleep should be bigger than 0\n"), -1);
	if (argc == 5)
	{
		state->number_of_times_each_philosopher_must_eat = ft_atoi_err(argv[4], (err = 0, &err));
		if (err || state->number_of_times_each_philosopher_must_eat <= 0)
			return (printf("number_of_times_each_philosopher_must_eat should be bigger than 0\n"), -1);
	}
	else
		state->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}

unsigned long mstime()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int safe_index(int i, int len)
{
	if (i >= 0 && i < len)
		return (i);
	if (i >= len)
		return (i % len);
	i *= -1;
	i %= (len + 1);
	if (i == 0)
		i = 1;
	return (len - i);
}

t_fork *init_forks(t_state *state)
{
	int	i;

	i = 0;
	t_fork *forks = malloc(state->number_of_philosophers * sizeof(t_fork));
	while (i < state->number_of_philosophers)
		pthread_mutex_init(&forks[i++].lock, NULL);
	return (forks);
}

t_philo *init_philos(t_state *state, t_fork *forks)
{
	int	i;

	i = 0;
	t_philo *philos = malloc(state->number_of_philosophers * sizeof(t_philo));
	while (i < state->number_of_philosophers)
	{
		if (i == state->number_of_philosophers - 1)
			philos[i].next = &philos[0];
		else
			philos[i].next = &philos[i + 1];
		philos[i].forks[FORK_RIGHT] = &forks[i];
		philos[i].forks[FORK_LEFT] = &forks[safe_index(i - 1, state->number_of_philosophers)];
		philos[i].first_fork = i % 2;
		philos[i].id = i + 1;
		philos[i].ms_last_meal = 0;
		philos[i].state = state;
		i++;
	}
	return (philos);
}

int	philo_eat(t_philo *philo)
{
	unsigned long	start;
	int				ret;
	t_state			*state;

	state = philo->state;
	pthread_mutex_lock(&philo->forks[philo->first_fork]->lock);
	philo_log(state, "has taken a fork", mstime(), philo->id);
	pthread_mutex_lock(&philo->forks[!philo->first_fork]->lock);
	philo_log(state, "has taken a fork", mstime(), philo->id);
	start = mstime();
	if (start - philo->ms_last_meal >= (unsigned)state->time_to_die)
		ret = -1;
	else
	{
		philo_log(state, "is eating", mstime(), philo->id);
		msleep(state->time_to_eat);
		ret = 0;
	}
	pthread_mutex_unlock(&philo->forks[!philo->first_fork]->lock);
	pthread_mutex_unlock(&philo->forks[philo->first_fork]->lock);
	philo->ms_last_meal = mstime();
	if (ret < 0)
	{
		philo_log(state, "died", start, philo->id);
		exit(1);
	}
	return (0);
}
// TODO: check if the philo will die during an activity
void	philo_sleep(t_philo *philo)
{
	t_state *state;

	state = philo->state;
	philo_log(state, "is sleeping", mstime(), philo->id);
	msleep(state->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	t_state *state;

	state = philo->state;
	philo_log(state, "is thinking", mstime(), philo->id);
	// TODO: this is to be calculated in a better way
	msleep(state->time_to_die - state->time_to_sleep);
}

void print_state(t_state *state)
{
	printf("state->number_of_philosophers = %d\n", state->number_of_philosophers);
	printf("state->time_to_die = %d\n", state->time_to_die);
	printf("state->time_to_eat = %d\n", state->time_to_eat);
	printf("state->time_to_sleep = %d\n", state->time_to_sleep);
	printf("state->number_of_times_each_philosopher_must_eat = %d\n", state->number_of_times_each_philosopher_must_eat);
}

void print_philo(t_philo *philo)
{
  printf("philo(%p)->id = %d\n", philo, philo->id);
  printf("philo(%p)->first_fork = %d\n", philo, philo->first_fork);
  printf("philo(%p)->ms_last_meal = %lu\n", philo, philo->ms_last_meal);
}

void *philosopher(void *arg)
{
	t_philo *philo;
	t_state *state;
	int		meals_count;

	philo = arg;
	state = philo->state;
	meals_count = 0;
	philo->ms_last_meal = mstime();
	/**
	 * eat
	 * sleep
	 * thing
	*/
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		meals_count++;
		if (state->number_of_times_each_philosopher_must_eat != -1
			&& meals_count >= state->number_of_times_each_philosopher_must_eat)
			return (NULL);
	}
}

int main(int argc, char **argv)
{
	t_state state;
	t_fork	*forks;
	t_philo	*philos;
	int		i;
	void	*thread_ret;

	i = 0;
	if (parse_args(argv + 1, argc - 1, &state) < 0)
		return (1);
	if (state.number_of_philosophers <= 0)
		return (0);

	forks = init_forks(&state);
	philos = init_philos(&state, forks);
	pthread_mutex_init(&state.display_lock, NULL);
	while (i < state.number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philosopher, &philos[i]);
		i++;
	}
	i = 0;
	while (i < state.number_of_philosophers)
	{
		pthread_join(philos[i].thread, &thread_ret);
		i++;
	}
	/**
	 * wait for threads
	 * deallocate resources
	*/
}
