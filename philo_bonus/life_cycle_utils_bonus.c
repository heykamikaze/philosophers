/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:08:35 by nbenjami          #+#    #+#             */
/*   Updated: 2022/06/01 20:08:38 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	*check_dead(void *args)
{
	t_philos	*philos;

	philos = (t_philos *)args;
	while (!philos->env->dead && philos->eaten_meals \
	< philos->env->nb_should_eat)
	{
		sem_wait(philos->env->check);
		if (get_time() - philos->time_to_die > philos->env->time_to_die)
		{
			philos->env->dead = 1;
			sem_wait(philos->env->print);
			printf("%ld\t%d philosopher is dead\n", \
			get_current_time(philos->env->start_time), philos->number);
			exit(EXIT_DEAD);
		}
		sem_post(philos->env->check);
	}
	return (NULL);
}

void	take_forks(t_philos *philos)
{
	sem_wait(philos->env->forks);
	sem_wait(philos->env->print);
	printf("%ld\tPhilosopher number %d taken first fork\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
	sem_wait(philos->env->forks);
	sem_wait(philos->env->print);
	printf("%ld\tPhilosopher number %d taken second fork\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
}

void	eat(t_philos *philos)
{
	sem_wait(philos->env->print);
	printf("%ld\tPhilosopher number %d is eating\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
	ft_usleep(philos->env->time_to_eat, philos->env->start_time);
	sem_wait(philos->env->check);
	philos->time_to_die = get_time();
	philos->eaten_meals++;
	sem_post(philos->env->check);
	sem_post(philos->env->forks);
	sem_post(philos->env->forks);
}

void	p_sleep(t_philos *philos)
{
	sem_wait(philos->env->print);
	printf("%ld\tPhilosopher number %d is sleeping\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
	ft_usleep(philos->env->time_to_sleep, philos->env->start_time);
}

void	think(t_philos *philos)
{
	sem_wait(philos->env->print);
	printf("%ld\tPhilosopher number %d is thinking\n", \
		get_current_time(philos->env->start_time), philos->number);
	sem_post(philos->env->print);
}
