/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/30 12:07:48 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

#include "philo.h"

void msleep(int msec)
{
	usleep(msec * 1000);
}

int	parse_args(char **argv, int argc, t_state *state)
{
	int	err;

	// TODO: make the last arg optional
	if (argc < 5)
		return (-1);
	// TODO: check error
	// TODO: number of philos couldn't be one
		
	state->number_of_philosophers = ft_atoi_err(argv[0], &err);
	state->time_to_die = ft_atoi_err(argv[1], &err);
	state->time_to_eat = ft_atoi_err(argv[2], &err);
	state->time_to_sleep = ft_atoi_err(argv[3], &err);
	state->number_of_times_each_philosopher_must_eat = ft_atoi_err(argv[4], &err);
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

t_fork *init_forks(int count)
{
	int	i;

	i = 0;
	t_fork *forks = malloc(count * sizeof(t_fork));
	while (i < count)
		pthread_mutex_init(&forks[i++].lock, NULL);
	return (forks);
}

t_philo *init_philos(int count, t_fork *forks)
{
	int	i;

	i = 0;
	t_philo *philos = malloc(count * sizeof(t_philo));
	while (i < count)
	{
		if (i == count - 1)
			philos[i].next = &philos[0];
		else
			philos[i].next = &philos[i + 1];
		philos[i].forks[FORK_RIGHT] = &forks[i];
		philos[i].forks[FORK_LEFT] = &forks[safe_index(i - 1, count)];
		philos[i].first_fork = i % 2;
		philos[i].id = i + 1;
		philos[i].ms_last_meal = 0;
		i++;
	}
	return (philos);
}

int	philo_eat(t_state *state, t_philo *philo)
{
	unsigned long	start;
	int				ret;

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
	pthread_mutex_unlock(&philo->forks[philo->first_fork]->lock);
	pthread_mutex_unlock(&philo->forks[!philo->first_fork]->lock);
	philo->ms_last_meal = mstime();
	if (ret < 0)
	{
		msleep(10);
		philo_log(state, "died", start, philo->id);
	}
	return (ret);
}

void	philo_sleep(t_state *state, t_philo *philo)
{
	philo_log(state, "is sleeping", mstime(), philo->id);
	msleep(state->time_to_sleep);
}

void	philo_think(t_state *state, t_philo *philo)
{
	philo_log(state, "is thinking", mstime(), philo->id);
	// TODO: this is to be calculated
	msleep(1);
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

void *print_comp(void *comp)
{
	// printf("++++++++state++++++++\n");
	// print_state(((void **)comp)[1]);
	// printf("++++++++++++++++\n");
	printf("++++++++philo++++++++\n");
	print_philo(((void **)comp)[0]);
	printf("++++++++++++++++\n");
	return NULL;
}

void *philosopher(void *philo_state)
{
	t_state *state;
	t_philo *philo;
	int		meals_count;

	philo = ((void **)philo_state)[0];
	state = ((void **)philo_state)[1];
	philo->first_fork = 99;
	pthread_mutex_lock(&state->display_lock);
	print_comp(philo_state);
	pthread_mutex_unlock(&state->display_lock);
	return (NULL);

	meals_count = 0;
	philo->ms_last_meal = mstime();
	/**
	 * eat
	 * sleep
	 * thing
	*/
	while (1)
	{
		if (philo_eat(state, philo) < 0)
			return ((void *)-1);
		philo_sleep(state, philo);
		philo_think(state, philo);
		meals_count++;
		if (meals_count == state->number_of_times_each_philosopher_must_eat)
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

	forks = init_forks(state.number_of_philosophers);
	philos = init_philos(state.number_of_philosophers, forks);
	pthread_mutex_init(&state.display_lock, NULL);
	// printf("------state------\n");
	// print_state(&state);
	// printf("------------\n");
	// printf("------philo------\n");
	// print_philo(&philos[0]);
	// printf("------------\n");

	void *comp[2];
	while (i < state.number_of_philosophers)
	{
		comp[0] = philos + i;
		comp[1] = &state;
		printf("------philo------\n");
		print_philo(comp[0]);
		printf("------------\n");
		pthread_create(&philos[i].thread, NULL, print_comp, comp);
		// pthread_create(&philos[i].thread, NULL, philosopher, comp);
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
