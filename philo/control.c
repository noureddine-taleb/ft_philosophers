/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:42:57 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/04 20:43:30 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

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
		philo_eat(philo);
		meals_count++;
		if (state->min_eat != -1
			&& meals_count >= state->min_eat)
			return (NULL);
		philo_sleep(philo);
		philo_think(philo);
	}
}
