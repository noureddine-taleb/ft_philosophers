/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/04 23:26:20 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_state	state;
	t_forks	*forks;
	t_philo	*philos;
	int		i;
	int		ret;

	i = 0;
	if (parse_args(argv, argc, &state) < 0)
		return (1);
	forks = init_forks(&state);
	if (!forks)
		exit(1);
	philos = init_philos(&state, forks);
	while (i < state.number_of_philosophers)
	{
		philo_create(&philos[i], &philosopher, &philos[i]);
		i++;
	}
	ret = wait_philos(philos, &state);
	if (ret)
		return (1);
	return (0);
}
