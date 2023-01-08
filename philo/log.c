/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:47:19 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 18:25:22 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

#ifdef BONUS

void	philo_log(t_philo *philo, char *event)
{
	sem_wait(philo->state->display_lock);
	printf("%ld %d %s\n", mstime(), philo->id, event);
	sem_post(philo->state->display_lock);
}
#else

void	philo_log(t_philo *philo, char *event)
{
	pthread_mutex_lock(&philo->state->display_lock);
	printf("%ld %d %s\n", mstime(), philo->id, event);
	pthread_mutex_unlock(&philo->state->display_lock);
}
#endif

void	philo_log_sleep(t_philo *philo)
{
	philo_log(philo, "is sleeping");
}

void	philo_log_think(t_philo *philo)
{
	philo_log(philo, "is thinking");
}

void	philo_log_eat(t_philo *philo)
{
	philo_log(philo, "is eating");
}
