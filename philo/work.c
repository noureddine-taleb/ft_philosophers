/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 18:32:10 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	philo_eat(t_philo *philo)
{
	get_forks(philo);
	if (check_death(philo))
		return ;
	philo->ms_last_meal = mstime();
	philo_log_eat(philo);
	msleep(philo, philo->state->time_to_eat);
	put_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	philo_log_sleep(philo);
	msleep(philo, philo->state->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	int		rem;

	rem = remaining(philo) - 5;
	philo_log_think(philo);
	if (rem > 0)
		msleep(philo, rem);
}
