/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 18:18:51 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_state			*state;

	state = philo->state;
	check_death(philo);
	get_fork(philo, philo->first_fork);
	check_death(philo);
	get_fork(philo, !philo->first_fork);
	check_death(philo);
	__philo_eat(philo);
	put_fork(philo, !philo->first_fork);
	put_fork(philo, philo->first_fork);
}

void	philo_sleep(t_philo *philo)
{
	t_state	*state;
	int		rem;

	state = philo->state;
	rem = check_death(philo);
	__philo_sleep(philo, rem);
}

void	philo_think(t_philo *philo)
{
	t_state	*state;
	int		rem;

	state = philo->state;
	rem = check_death(philo);
	__philo_think(philo, rem);
}
