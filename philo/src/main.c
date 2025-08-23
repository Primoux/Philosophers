#include "philo.h"
#include "style.h"

void	*thread_start(void *arg)
{
	(void)arg;
	printf("%sHello from the thread%s\n", GREEN, RST);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, thread_start, NULL);
	pthread_join(thread, NULL);
	printf("%sHello from the main%s\n", RED, RST);
	return (0);
}
