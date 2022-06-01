/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:28:30 by nbenjami          #+#    #+#             */
/*   Updated: 2022/06/02 00:20:48 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
}

long	get_current_time(long time)
{
	struct timeval	*start_time;
	time_t			current;

	start_time = malloc(sizeof(struct timeval) * 1);
	gettimeofday(start_time, NULL);
	current = start_time->tv_sec * 1000 + start_time->tv_usec / 1000;
	return (current - time);
}
