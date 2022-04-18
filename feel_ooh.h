#ifndef	FEEL_OOH_H
# define FEEL_OOH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# define Sleep(X) sleep(X)
# define wait() scanf("1")

# define PHT_SIZE 5
# define pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER

typedef struct philosopher_tag {
    const char *name;
    unsigned left_fork;
    unsigned right_fork;
} philosopher_t;

typedef struct table_tag {
    pthread_mutex_t forks[PHT_SIZE];
} table_t;
 
typedef struct philosopher_args_tag {
    const philosopher_t *philosopher;
    const table_t *table;
} philosopher_args_t;


#endif