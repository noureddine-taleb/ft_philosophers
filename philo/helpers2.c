/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:10:00 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 18:23:18 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	__perror(char *err)
{
	int	len;

	len = 0;
	while (err[len])
		len++;
	write(2, err, len);
}

void	help(char *program)
{
	__perror(program);
	__perror(" number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	parse_args(char **argv, int argc, t_state *state)
{
	if (--argc < 4)
		return (help(*argv), -1);
	argv++;
	if (parse_int(argv[0], &state->number_of_philosophers, 1) < 0)
		return (__perror("number of philosophers should be bigger than 0\n"),
			-1);
	if (parse_int(argv[1], &state->time_to_die, 1) < 0)
		return (__perror("time to die should be bigger than 0\n"), -1);
	if (parse_int(argv[2], &state->time_to_eat, 1) < 0)
		return (__perror("time to eat should be bigger than 0\n"), -1);
	if (parse_int(argv[3], &state->time_to_sleep, 1) < 0)
		return (__perror("time to sleep should be bigger than 0\n"), -1);
	if (argc == 5)
	{
		if (parse_int(argv[4], &state->min_eat, 1) < 0)
			return (__perror("number of times each philosopher must eat\
 should be bigger than 0\n"), -1);
	}
	else
		state->min_eat = -1;
	return (0);
}
