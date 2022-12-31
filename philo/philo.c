/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 18:11:31 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help(void)
{
	printf("./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	parse_int(char *str, int *i, int min)
{
	int	err;

	err = 0;
	*i = ft_atoi_err(str, &err);
	if (err || *i <= min)
		return (-1);
	return (0);
}

/**
 * TODO: remove warn
*/
int	parse_args(char **argv, int argc, t_state *state)
{
	if (argc < 4)
		return (help(), -1);
	if (parse_int(argv[0], &state->number_of_philosophers, 2) < 0)
		return (printf("number of philosophers should be bigger than 1\n"), -1);
	if (parse_int(argv[1], &state->time_to_die, 1) < 0)
		return (printf("time to die should be bigger than 0\n"), -1);
	if (parse_int(argv[2], &state->time_to_eat, 1) < 0)
		return (printf("time to eat should be bigger than 0\n"), -1);
	if (parse_int(argv[3], &state->time_to_sleep, 1) < 0)
		return (printf("time to sleep should be bigger than 0\n"), -1);
	if (argc == 5)
	{
		if (parse_int(argv[3], &state->min_eat, 1) < 0)
			return (printf("number of times each philosopher must eat\
 should be bigger than 0\n"), -1);
	}
	else
		state->min_eat = -1;
	if (state->time_to_die <= state->time_to_eat + state->time_to_sleep)
		printf("warn:  time to die is not bigger enough\n");
	return (0);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_state	*state;
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
		if (state->min_eat != -1
			&& meals_count >= state->min_eat)
			return (NULL);
	}
}

int	main(int argc, char **argv)
{
	t_state	state;
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
		pthread_join(philos[i++].thread, &thread_ret);
	return (0);
}
