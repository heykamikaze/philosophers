/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:45:50 by nbenjami          #+#    #+#             */
/*   Updated: 2022/04/28 20:43:36 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <machine/types.h>

# define DIED " died\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define FORK " has taken a fork\n"
# define DONE " all philosophers have eaten enough\n"

struct	s_phil;

typedef struct s_table
{
	int						n_of_philos;
	long					start_time;
	long					t_to_sleep;
	long					t_to_eat;
	long					t_to_die;
	int						dead_count;
	long					numb_to_eat;
	struct s_phil			*phil;
	pthread_mutex_t			*forks_m;
	pthread_mutex_t			message_m;
	pthread_mutex_t			death_mutex;

}	t_table;

typedef struct s_phil
{
	int				num;
	int				eat_flag;
	time_t			death_time;
	int				eat_last_time;
	int				left_fork;
	int				right_fork;
	int				meals_counter;
	struct s_table	*table;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}	t_phil;

int		ft_arg_check(char **argv, int argc, t_table *table);
int		ft_atoi(const char *str);
int		ft_is_digit(int c);
void	ft_exit(int index);
void	ft_start_table(t_table *table);
int		ft_start_mutex(t_table *table);
long	ft_get_time(long time);
long	ft_get_time(long time);
char	*ft_message(int status_code);
void	ft_state(t_phil *phil, int status_code);
void	*ft_cycle(void *ptr);
void	*ft_spectator(void *phil);
void	*ft_process(void *phil);
int		ft_run_phil(t_table *table);
void	ft_usleep(time_t millisec, long start_time);
void	ft_drop_fork(t_phil *philo);
void	ft_eat(t_phil *philo);
void	ft_take_fork(t_phil *philo);
void	ft_putstr(char *s);
void	ft_putnbr(long n);
void	ft_putchar(char c);
void	ft_free(t_table *table);

#endif