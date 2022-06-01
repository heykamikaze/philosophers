/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:47:06 by nbenjami          #+#    #+#             */
/*   Updated: 2022/06/02 00:20:57 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define EXIT_DEAD 1
# define EXIT_ALIVE 0
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_env	t_env;

typedef struct s_philos	t_philos;

typedef struct s_philos
{
	int				eaten_meals;
	int				number;
	t_env			*env;
	time_t			time_to_die;
	pid_t			pid;
	pthread_t		dead;
}				t_philos;

typedef struct s_env
{
	int				nb_should_eat;
	int				nb_philos;
	int				dead;
	t_philos		*philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	sem_t			*print;
	sem_t			*check;
	sem_t			*forks;
}				t_env;

int		ft_atoi(char *str);

void	*check_dead(void *args);
void	take_forks(t_philos *philos);
void	eat(t_philos *philos);
void	p_sleep(t_philos *philos);
void	think(t_philos *philos);

int		check_param(int argc, char **argv);
void	creating_threads(t_env *env);
long	get_time(void);
long	get_current_time(long time);
void	*life_cycle(void *obj);
int		init_env(t_env *env, char **argv, int argc);
void	ft_usleep(time_t milisec, long start_time);

#endif