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

typedef struct s_table
{
    int     n_of_philos;
    long    t_to_sleep;
    long    t_to_eat;
    long    t_to_die;
    long    numb_to_eat;
} t_table;

#endif