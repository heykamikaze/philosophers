/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:44:01 by nbenjami          #+#    #+#             */
/*   Updated: 2022/04/28 20:50:00 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_check(char **argv, int argc, t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
			if (!ft_is_digit(argv[i][j++]))
				return (0);
	}
	table->n_of_philos = ft_atoi(argv[1]);
	table->t_to_die = ft_atoi(argv[2]);
	table->t_to_eat = ft_atoi(argv[3]);
	table->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->numb_to_eat = ft_atoi(argv[5]);
	else
		table->numb_to_eat = -1;
	table->forks_m = NULL;
	table->phil = NULL;
	table->phil = malloc(sizeof(t_phil) * table->n_of_philos);
	if (!table->phil)
		return (0);
	return (1);
}

void	ft_free(t_table *table)
{
	int	i = -1;
	while (++i < table->n_of_philos)
	{
		pthread_mutex_destroy(&table->phil[i].eat_m);
		pthread_mutex_destroy(&table->phil[i].mutex);
		pthread_mutex_destroy(&table->forks_m[i]);
	}
	free (table->phil);
	free(table->forks_m);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->message_m);
	free(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (0);
	if ((argc == 5 || argc == 6) && ft_arg_check(argv, argc, table))
	{
		ft_start_table(table);
		if (!ft_start_mutex(table))
			return (1);
	}
	else
		return (0);
	ft_run_phil(table);
	pthread_mutex_lock(&table->death_mutex);
	pthread_mutex_unlock(&table->death_mutex);
	ft_free(table);
	return (0);
}
