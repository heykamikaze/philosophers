#include "philo.h"

void	ft_start_mutex(t_table *table)
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