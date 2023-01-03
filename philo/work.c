/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/03 14:55:53 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	philo_eat(t_philo *philo)
{
	check_death(philo);
	get_fork(philo, philo->first_fork);
	// check_death(philo);
	get_fork(philo, !philo->first_fork);
	// check_death(philo);
	philo->ms_last_meal = mstime();
	__philo_eat(philo, philo->ms_last_meal);
	put_fork(philo, !philo->first_fork);
	put_fork(philo, philo->first_fork);
}

void	philo_sleep(t_philo *philo)
{
	int		rem;

	rem = check_death(philo);
	__philo_sleep(philo, rem);
}

void	philo_think(t_philo *philo)
{
	int		rem;

	rem = check_death(philo);
	__philo_think(philo, rem);
}
