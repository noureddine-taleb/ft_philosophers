/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:35:16 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 17:19:11 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	mstime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	safe_index(int i, int len)
{
	if (i >= 0 && i < len)
		return (i);
	if (i >= len)
		return (i % len);
	i *= -1;
	i -= 1;
	i %= len;
	return (len - 1 - i);
}

void	msleep(int msec)
{
	usleep(msec * 1000);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
