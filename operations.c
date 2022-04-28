/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:45:27 by nbenjami          #+#    #+#             */
/*   Updated: 2022/04/27 19:08:06 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_phil *philo)
{
	// if (philo->num % 2 == 0)
	// {
		pthread_mutex_lock(&philo->table->forks_m[philo->left_fork]);
		ft_state(philo, 4);
		pthread_mutex_lock(&philo->table->forks_m[philo->right_fork]);
		ft_state(philo, 4);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->table->forks_m[philo->right_fork]);
	// 	ft_state(philo, 4);
	// 	pthread_mutex_lock(&philo->table->forks_m[philo->left_fork]);
	// 	ft_state(philo, 4);
	// }
}

void	ft_eat(t_phil *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->eat_flag = 1;
	philo->eat_last_time = ft_get_time(philo->table->start_time);
	philo->death_time = philo->eat_last_time + philo->table->t_to_die;
	ft_state(philo, 1);
	ft_usleep(philo->table->t_to_eat, philo->table->start_time);
	philo->meals_counter += 1;
	philo->eat_flag = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_m);
}

void	ft_drop_fork(t_phil *philo)
{
	ft_state(philo, 2);
	pthread_mutex_unlock(&philo->table->forks_m[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks_m[philo->right_fork]);
	ft_usleep(philo->table->t_to_sleep, philo->table->start_time);
}

void	ft_usleep(time_t millisec, long start_time)
{
	time_t	stop;
	time_t	start;

	stop = ft_get_time(start_time) + millisec;
	start = ft_get_time(start_time);
	while (start < stop)
	{
		usleep(1);
		start = ft_get_time(start_time);
	}
}
