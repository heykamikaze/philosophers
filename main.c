//example of deadlock wiht t he random waiting time 

#include "philo.h"
// #include <pthread.h>
// #include <stdlib.h>
// #include <stdio.h>
 
// #ifdef WIN32
//     #include <conio.h>
//     #include <Windows.h>
//     #define Sleep(X) Sleep(X)
//     #define wait() _getch()
// #else
//     #include <unistd.h>
//     #define Sleep(X) sleep(X)
//     #define wait() scanf("1")
// #endif
 
// #define PHT_SIZE 5
 
// typedef struct philosopher_tag {
//     const char *name;
//     unsigned left_fork;
//     unsigned right_fork;
// } philosopher_t;
 
// typedef struct table_tag {
//     pthread_mutex_t forks[PHT_SIZE];
// } table_t;
 
// typedef struct philosopher_args_tag {
//     const philosopher_t *philosopher;
//     const table_t *table;
// } philosopher_args_t;
 
// pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;
 
// void init_philosopher(philosopher_t *philosopher, 
//                       const char *name, 
//                       unsigned left_fork,
//                       unsigned right_fork) {
//     philosopher->name = name;
//     philosopher->left_fork = left_fork;
//     philosopher->right_fork = right_fork;
// }
 
// void init_table(table_t *table) {
//     size_t i;
//     for (i = 0; i < PHT_SIZE; i++) {
//         pthread_mutex_init(&table->forks[i], NULL);
//     }
// }
// void	rand_s(unsigned int *rand)
// {
// 	srand(*rand);
// }

// void* eat(void *args) {
//     philosopher_args_t *arg = (philosopher_args_t*) args;
//     const philosopher_t *philosopher = arg->philosopher;
//     const table_t *table = arg->table;
//     unsigned rand;  
 
//     do {
//         printf("%s started dinner\n", philosopher->name);
 
//         pthread_mutex_lock(&entry_point);
//         pthread_mutex_lock(&table->forks[philosopher->left_fork]);
//         rand_s(&rand);
//         rand %= 1000;
//         Sleep(rand);
//         pthread_mutex_lock(&table->forks[philosopher->right_fork]);
//         pthread_mutex_unlock(&entry_point);
 
//         printf("%s is eating after %d ms sleep\n", philosopher->name, rand);
 
//         pthread_mutex_unlock(&table->forks[philosopher->right_fork]);
//         pthread_mutex_unlock(&table->forks[philosopher->left_fork]);
 
//         printf("%s finished dinner\n", philosopher->name);
//     } while (1);
// }
 
// void main() {
//     pthread_t threads[PHT_SIZE];
//     philosopher_t philosophers[PHT_SIZE];
//     philosopher_args_t arguments[PHT_SIZE];
//     table_t table;
//     size_t i;
 
//     init_table(&table);
 
//     init_philosopher(&philosophers[0], "Alice", 0, 1);
//     init_philosopher(&philosophers[1], "Bob",   1, 2);
//     init_philosopher(&philosophers[2], "Clark", 2, 3);
//     init_philosopher(&philosophers[3], "Denis", 3, 4);
//     init_philosopher(&philosophers[4], "Eugin", 4, 0);
 
//     for (i = 0; i < PHT_SIZE; i++) {
//         arguments[i].philosopher = &philosophers[i];
//         arguments[i].table = &table;
//     }
 
//     for (i = 0; i < PHT_SIZE; i++) {
//         pthread_create(&threads[i], NULL, eat, &arguments[i]);
//     }
 
//     for (i = 0; i < PHT_SIZE; i++) {
//         pthread_join(threads[i], NULL);
//     }
// }

void	ft_arg_check(char **argv, int argc, t_table *table) //checks argc, init struct elements
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
			ft_is_digit(argv[i][j++]);
		i++;
	}
	table->n_of_philos = ft_atoi(argv[1]);
	table->t_to_die = ft_atoi(argv[2]);
	table->t_to_eat = ft_atoi(argv[3]);
	table->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->numb_to_eat = ft_atoi(argv[5]);
	table->forks_m = NULL;
	table->phil = NULL;
	table->phil = malloc(sizeof(t_phil) * table->n_of_philos);
	if (!table->phil)
		ft_exit(1);
}


int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
		if (!table)
			ft_exit(1);
	if (argc == 5 || argc == 6)
	{
		ft_arg_check(argv, argc, table);
		ft_start_table(table);//старт 
		ft_start_mutex(table);//все в ините с мьютексами 
	}
	else 
		ft_exit(2);
	ft_run_phil(table);
	pthread_mutex_lock(&table->death_mutex);
	pthread_mutex_unlock(&table->death_mutex);
	// printf("n_of_philos %d\n", table->n_of_philos);
	// printf("t_to_die %d\n", table->t_to_die);
	// printf("t_to_eat %d\n", table->t_to_eat);
	// printf("t_to_sleep %d\n", table->t_to_sleep);
	// printf("numb_to_eat %d\n", table->numb_to_eat);
	return (0);
}
