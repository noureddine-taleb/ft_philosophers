/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:27 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 14:33:08 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

int	wait_philos(t_philo	*philos)
{
	int		i;
	void	*ret;
	int		status;

	i = 0;
	status = 0;
	while (i < philos->state->number_of_philosophers)
	{
		pthread_join(philos[i++].thread, &ret);
		if (ret == PHILO_FAILURE)
			status = 1;
	}
	return (status);
}

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
	return (wait_philos(philos));
}
