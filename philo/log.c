/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:47:19 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 10:46:58 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_log(t_philo *philo, char *event)
{
	// pthread_mutex_lock(&state->display_lock);
	printf("%ld %d %s\n", mstime(), philo->id, event);
	// pthread_mutex_unlock(&state->display_lock);
}

void philo_log_sleep(t_philo *philo)
{
	philo_log(philo, "is sleeping");
}

void philo_log_think(t_philo *philo)
{
	philo_log(philo, "is thinking");
}

void philo_log_eat(t_philo *philo)
{
	philo_log(philo, "is eating");
}

void philo_log_take_fork(t_philo *philo)
{
	philo_log(philo, "has taken a fork");
}

void philo_log_death(t_philo *philo)
{
	philo_log(philo, "died");
}
