#include <unistd.h>
#include <pthread.h>
#include <string.h>

// void *print(void *buf)
// {
// 	for (int i = 0; i < 20; i++) {
// 		write(1, (char *)buf, strlen(buf));
// 		usleep(100000);
// 	}
// 	return(NULL);
// }

// int main()
// {
// 	char *str1 = "x_x_x_x_x_x_x_x_x_x_\n";
// 	char *str2 = "o_o_o_o_o_o_o_o_o_o_\n";

// 	pthread_t t1, t2;

// 		pthread_create(&t1, NULL, print, (void *)str1);
// 		pthread_create(&t2, NULL, print, (void *)str2);

// 		pthread_join(t1, NULL);
// 		pthread_join(t2, NULL);
// 		// usleep(3000000);
// 		write(1, "Exit\n", 5);
// }

void* routine() {
	printf("test from threads\n");
	sleep(3);
	printf("ending thread");
}

int	main(int argc, char* argv[]) {
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0) {
		return (2);
	}
	if (pthread_join(t1, NULL) != 0) {
		return (3);
	}
	if (pthread_join(t2, NULL) != 0 ){
		return (4);
	}
	return 0;
}