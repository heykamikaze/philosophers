/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:06:38 by nbenjami          #+#    #+#             */
/*   Updated: 2022/06/01 20:06:42 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_env *env)
{
	sem_unlink("/check");
	sem_unlink("/forks");
	sem_unlink("/print");
	env->check = sem_open("/check", O_CREAT, 0666, 1);
	env->forks = sem_open("/forks", O_CREAT, 0666, env->nb_philos);
	env->print = sem_open("/print", O_CREAT, 0666, 1);
	sem_unlink("/check");
	sem_unlink("/forks");
	sem_unlink("/print");
	if (env->check == SEM_FAILED || env->forks == SEM_FAILED \
	|| env->print == SEM_FAILED)
		return (0);
	return (1);
}

static int	get_filos(t_env *env)
{
	int	i;

	i = -1;
	env->dead = 0;
	env->philos = malloc(sizeof(t_philos) * env->nb_philos);
	if (!env->philos)
		return (0);
	while (++i < env->nb_philos)
	{
		env->philos[i].eaten_meals = 0;
		env->philos[i].number = i + 1;
		env->philos[i].env = env;
	}
	return (1);
}

int	init_env(t_env *env, char **argv, int argc)
{
	env->nb_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->nb_should_eat = ft_atoi(argv[5]);
	else
		env->nb_should_eat = INT_MAX;
	if (!get_filos(env))
	{
		printf("Error (malloc).");
		return (0);
	}
	if (!init_sem(env))
	{
		printf("Error (init sem).");
		return (0);
	}
	return (1);
}
