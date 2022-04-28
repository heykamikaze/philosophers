/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:22:44 by nbenjami          #+#    #+#             */
/*   Updated: 2022/04/28 20:10:16 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->message_m, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_lock(&table->death_mutex);
	table->forks_m = malloc(sizeof(pthread_mutex_t) * table->n_of_philos);
	if (!table->forks_m)
		return (0);
	while (i < table->n_of_philos)
		pthread_mutex_init(&table->forks_m[i++], NULL);
	return (1);
}

void	ft_start_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_of_philos)
	{
		table->phil[i].meals_counter = 0;
		table->phil[i].num = i;
		table->phil[i].left_fork = i;
		table->phil[i].right_fork = (i + 1) % table->n_of_philos;
		table->phil[i].table = table;
		table->dead_count = 0;
		if (table->n_of_philos == 1)
			table->phil[i].eat_flag = 0;
		else
			table->phil[i].eat_flag = 1;
		pthread_mutex_init(&table->phil[i].mutex, NULL);
		pthread_mutex_init(&table->phil[i].eat_m, NULL);
		pthread_mutex_lock(&table->phil[i].eat_m);
		i++;
	}
}

long	ft_get_time(long time)
{
	struct timeval	start_time;
	long			current;

	gettimeofday(&start_time, NULL);
	current = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	return (current - time);
}

char	*ft_message(int status_code)
{
	if (status_code == 0)
		return (DIED);
	if (status_code == 1)
		return (EAT);
	if (status_code == 2)
		return (SLEEP);
	if (status_code == 3)
		return (THINK);
	if (status_code == 4)
		return (FORK);
	if (status_code == 5)
		return (DONE);
	return ("");
}

void	ft_state(t_phil *phil, int status_code)
{
	static int	done;

	pthread_mutex_lock(&phil->table->message_m);
	if (done == 0)
	{
		if (status_code == 0)
		{
			phil->table->dead_count = 1;
			ft_putnbr(ft_get_time(phil->table->start_time));
			ft_putchar(32);
			if (status_code != 5)
				ft_putnbr(phil->num + 1);
			ft_putstr(ft_message(status_code));
			done = 1;
			return ;
		}
		else
		{
			ft_putnbr(ft_get_time(phil->table->start_time));
			ft_putchar(32);
			if (status_code != 5)
				ft_putnbr(phil->num + 1);
			if (status_code == 5 || status_code == 0)
				done = 1;
			if (phil->table->dead_count == 0)
				ft_putstr(ft_message(status_code));
		}
	}
	pthread_mutex_unlock(&phil->table->message_m);
}
