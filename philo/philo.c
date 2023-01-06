/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/06 16:37:18 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

int	main(int argc, char **argv)
{
	t_state	state;
	t_fork	*forks;
	t_philo	*philos;
	int		i;

	i = 0;
	if (parse_args(argv, argc, &state) < 0)
		return (1);
	forks = init_forks(&state);
	philos = init_philos(&state, forks);
	while (i < state.number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philosopher, &philos[i]);
		i++;
	}
	i = 0;
	while (i < state.number_of_philosophers)
		pthread_detach(philos[i++].thread);
	pthread_exit(NULL);
	return (0);
}
