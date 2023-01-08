/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:22:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 18:25:13 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

#ifdef BONUS

int	check_death(t_philo *philo)
{
	long	rem;

	rem = remaining(philo);
	if (rem <= 0)
		exit ((philo_log_death(philo), 1));
	return (0);
}
#else

int	check_death(t_philo *philo)
{
	long	rem;

	rem = remaining(philo);
	if (philo->state->died)
		return (1);
	if (rem <= 0)
		return (philo_log_death(philo), philo->state->died = 1, 1);
	return (0);
}
#endif

int	remaining(t_philo *philo)
{
	unsigned long	curtime;

	curtime = mstime();
	return (philo->state->time_to_die - (curtime - philo->ms_last_meal));
}
