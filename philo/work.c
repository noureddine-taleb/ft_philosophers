/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/04 16:49:18 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	philo_eat(t_philo *philo)
{
	int		rem;

	check_death(philo);
	get_forks(philo);
	philo->ms_last_meal = mstime();
	rem = check_death(philo);
	__philo_eat(philo, rem);
	put_forks(philo);
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
