/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:47:19 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/07 11:42:14 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	philo_log(t_philo *philo, char *event)
{
	printf("%ld %d %s\n", mstime(), philo->id, event);
}

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

void	philo_log_take_fork(t_philo *philo)
{
	philo_log(philo, "has taken a fork");
}
