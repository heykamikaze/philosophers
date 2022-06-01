/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:07:04 by nbenjami          #+#    #+#             */
/*   Updated: 2022/06/02 00:20:53 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*life_cycle(void *obj)
{
	t_philos	*philos;

	philos = (t_philos *)obj;
	pthread_create(&philos->dead, NULL, check_dead, (void *)philos);
	if (philos->number % 2 == 0)
		ft_usleep(philos->env->time_to_eat / 10, philos->env->start_time);
	while (!(philos->env->dead))
	{
		take_forks(philos);
		eat(philos);
		if (philos->eaten_meals >= philos->env->nb_should_eat)
			break ;
		p_sleep(philos);
		think(philos);
	}
	pthread_join(philos->dead, NULL);
	exit(EXIT_ALIVE);
	return (obj);
}
