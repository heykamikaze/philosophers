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
		ft_exit(1);
	while (i < table->n_of_philos)
		pthread_mutex_init(&table->forks_m[i++], NULL);//use counter here?
	return (0);
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
		table->phil[i].right_fork  = (i + 1) % table->n_of_philos;
		table->phil[i].table = table;
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


char *ft_message(int status_code)
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

	done = 0;
	pthread_mutex_lock(&phil->table->message_m);
	if (done == 0)
	{
		ft_putnbr(ft_get_time(phil->table->start_time));
		ft_putchar(32);
		if (status_code != 5)
			ft_putnbr(phil->num + 1);
		if (status_code == 5 || status_code == 0)
			done = 1;
		ft_putstr(ft_message(status_code));
	}
	pthread_mutex_unlock(&phil->table->message_m);
}

void	*ft_cycle(void *ptr)
{
	t_table	*table;
	int	i;
	int	count;

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
	if (count == table->numb_to_eat) //локай стдин перед выходом 
		exit(1);
	else
		pthread_mutex_unlock(&table->death_mutex);
	return (NULL);

}


void	*ft_spectator(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->eat_flag && ft_get_time(philo->table->start_time) >= philo->death_time)
		{
			ft_state(philo, 0);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->table->death_mutex);
			return(NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(10000);
	}
}


void	*ft_process(void *phil)
{
	t_phil	*philo;
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
	int	i;
	pthread_t	t1;
	void	*phil;

	i = 0;
	table->start_time = 0;
	table->start_time = ft_get_time(table->start_time);
	if (table->numb_to_eat != 0)
	{
		if (pthread_create(&t1, NULL, &ft_cycle, (void *)table) != 0)//ft_cycle)
			return (1);
		pthread_detach(t1);
	}
	while (i < table->n_of_philos)
	{
		phil = (void *)(&table->phil[i]);
		if (pthread_create(&t1, NULL, &ft_process, (void *)(&table->phil[i])) != 0) //live
			return (1);
		pthread_detach(t1);
		usleep(500);
		i++;
	}
	return(0);
}