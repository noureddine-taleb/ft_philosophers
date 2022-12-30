/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:47:19 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/30 10:45:35 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log(t_state *state, char *event, unsigned long mstimestamp, int philo)
{
	pthread_mutex_lock(&state->display_lock);
	printf("%ld %d %s\n", mstimestamp, philo, event);
	pthread_mutex_unlock(&state->display_lock);
}