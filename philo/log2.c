/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:24:02 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 18:24:02 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	philo_log_death(t_philo *philo)
{
	philo_log(philo, "died");
}

void	philo_log_take_fork(t_philo *philo)
{
	philo_log(philo, "has taken a fork");
}
