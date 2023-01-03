/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:59:34 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/03 12:46:11 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philosopher(void *arg)
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
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		meals_count++;
		if (state->min_eat != -1
			&& meals_count >= state->min_eat)
			return (0);
	}
}

void	philo_create(t_philo *philo, int (*fn) (void *), void *arg)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		philo->pid = pid;
		return ;
	}
	else
	{
		exit(fn(arg));
	}
}

int	philo_join(t_philo *philos, t_state	*state)
{
	int	status;
	int	pid;
	int	i;

	i = 0;
	pid = wait(&status);
	while (i < state->number_of_philosophers)
	{
		if (philos[i].pid == pid)
		{
			philos[i].finished = 1;
			break ;
		}
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status));
}

void	philo_kill_remaining(t_philo *philos, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (!philos[i].finished)
			kill(philos[i].pid, SIGINT);
		i++;
	}
}

int	wait_philos(t_philo *philos, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		if ((philo_join(philos, state)))
			return (philo_kill_remaining(philos, state), -1);
		i++;
	}
	return (0);
}
