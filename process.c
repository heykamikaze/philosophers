/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:23:30 by nbenjami          #+#    #+#             */
/*   Updated: 2022/04/28 19:51:57 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_process(void *phil)
{
	t_phil		*philo;
	pthread_t	t2;

	philo = (t_phil *)phil;
	philo->eat_last_time = ft_get_time(philo->table->start_time);
	philo->death_time = philo->eat_last_time + philo->table->t_to_die;
	if (pthread_create(&t2, NULL, &ft_spectator, phil) != 0)
		return ((void *)1);
	pthread_detach(t2);
	while (1)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_drop_fork(philo);
		ft_state(philo, 3);
	}
	return ((void *)0);
}

int	ft_run_phil(t_table *table)
{
	int			i;
	pthread_t	t1;
	void		*phil;

	i = 0;
	table->start_time = 0;
	table->start_time = ft_get_time(table->start_time);
	if (table->numb_to_eat != -1)
	{
		if (pthread_create(&t1, NULL, &ft_cycle, (void *)table) != 0)
			return (1);
		pthread_detach(t1);
	}
	while (i < table->n_of_philos)
	{
		phil = (void *)(&table->phil[i]);
		if (pthread_create(&t1, NULL, &ft_process,
				(void *)(&table->phil[i])) != 0)
			return (1);
		pthread_detach(t1);
		usleep(500);
		i++;
	}
	return (0);
}

void	*ft_spectator(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->eat_flag
			&& ft_get_time(philo->table->start_time) >= philo->death_time)
		{
			ft_state(philo, 0);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->table->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(10000);
	}
}

void	*ft_cycle(void *ptr)
{
	t_table	*table;
	int		i;
	int		count;

	table = (t_table *)ptr;
	count = 0;
	while (count < table->numb_to_eat)
	{
		i = 0;
		while (i < table->n_of_philos)
		{
			pthread_mutex_lock(&table->phil[i].eat_m);
			i++;
		}
		count++;
	}
	ft_state(&table->phil[0], 5);
	if (count == table->numb_to_eat)
		pthread_mutex_lock(&table->message_m);
	else
		pthread_mutex_unlock(&table->death_mutex);
	return (NULL);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
