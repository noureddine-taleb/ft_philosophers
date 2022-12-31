/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 16:29:42 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

#include "philo.h"

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
	while (1)
	{
		philo->work[0](philo);
		philo->work[1](philo);
		philo->work[2](philo);
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
	return (0);
}
