#ifndef	PHILO_H
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

# define DIED "  died\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define FORK " has taken a fork\n"
# define DONE " all philosophers have eaten enough\n"

typedef struct s_phil
{
    int	num; //philo number
	int	eat_flag; //status if the philo has eaten or not 
	time_t	death_time; //how much time left as for now before the philo dies 
	int	eat_last_time; //the timestamp this philo has eaten last time
	int	left_fork; //left fork number 
	int	right_fork;//right fork number 
	int	meals_counter;//how many times the philo has eaten already 
	struct	s_table	*table;//to get the access to general struct with the info regarding timestamps and food
	pthread_mutex_t	mutex;//mutexes for eating process
	pthread_mutex_t	eat_m;
}   t_phil;

typedef struct s_table
{
    int     n_of_philos;//number of philosophers 
	long	start_time; //start time
    long    t_to_sleep;//how much time the philo is supposed to be sleepin
    long    t_to_eat;//eating time
    long    t_to_die;//max time the philo could possibly live
    long    numb_to_eat;//how many times at least the philo has to eat before death 
    t_phil  *phil;//philo struct
	int		start;//time to start
	pthread_mutex_t	*forks_m;//forks mutex
	pthread_mutex_t message_m; //message mutex
	pthread_mutex_t	death_mutex; //when a philo dies mutex 

} t_table;


void	ft_arg_check(char **argv, int argc, t_table *table);
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
int	ft_run_phil(t_table *table);
void	ft_usleep(time_t millisec, long start_time);
void	ft_drop_fork(t_phil *philo);
void	ft_eat(t_phil *philo);
void	ft_take_fork(t_phil *philo);
void	ft_putstr(char *s);
void	ft_putnbr(long n);
void	ft_putchar(char c);

#endif