/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/04 18:53:51 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	check_death(philo);
	get_forks(philo);
	philo->ms_last_meal = mstime();
	__philo_eat(philo, philo->ms_last_meal);
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
