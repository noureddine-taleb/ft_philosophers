/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:35:16 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 12:12:26 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

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
	int	start;

	start = mstime();
	while ((int)mstime() - start < msec)
		usleep(50);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	parse_int(char *str, int *i, int min)
{
	int	err;

	err = 0;
	*i = ft_atoi_err(str, &err);
	if (err || *i < min)
		return (-1);
	return (0);
}
