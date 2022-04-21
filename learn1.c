#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>


//you can have inside of process multiple threads; regarding the address space: variable if threads are visible from all threads 
int x = 2;


void* routine() {
	x++;
	sleep(2);
	printf("Value of x %d\n", x);
}

void* routine2() {
	sleep(2);
	printf("Value of x %d\n", x);
}

int	main(int argc, char* argv[]) {
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL)) {
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine2, NULL)) {
		return (1);
	}
	if (pthread_join(t1, NULL)) {
		return 2;
	}
	if (pthread_join(t2, NULL)) {
		return 2;
	}
	return 0;
}

// int	main(int argc, char* argv[]) {
// 	int x = 2;
// 	int	pid = fork();
// 	if (pid == -1) {
// 		return 1;
// 	}

// 	if (pid == 0) {
// 		x++;
// 	}
// 	sleep(2);
// 	printf ("Value of x: %d\n", x);

// 	// printf("Process ID %d\n", getpid());
// 	if (pid != 0)
// 	{
// 		wait(NULL);
// 	}
//  }