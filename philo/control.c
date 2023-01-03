/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:42:57 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/03 12:45:13 by ntaleb           ###   ########.fr       */
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
		philo_sleep(philo);
		philo_think(philo);
		meals_count++;
		if (state->min_eat != -1
			&& meals_count >= state->min_eat)
			return (NULL);
	}
}
