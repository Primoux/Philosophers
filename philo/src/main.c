#include "philo.h"
#include "style.h"

int				a = 0;
pthread_mutex_t	mutex;
int				count;

void	*thread_start(void *arg)
{
	int	i;
	int j = 0;

	i = *(int *)arg;
	// printf("%sBjr je suis nouveau%s\n", BLUE, RST);
	while (j < count)
	{
		pthread_mutex_lock(&mutex);
		printf("%sLe thread[%d] 1 a  %d %s\n", GREEN, i, a, RED);
		a++;
		pthread_mutex_unlock(&mutex);
		j++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*thread;
	int			nbr_thread;
	int			i;
	
	nbr_thread = atoi(argv[1]);
	int			ids[nbr_thread];
	i = 0;
	if (argc != 3)
	{
		printf("T con ou quoi\n");
		return (1);
	}
	for (int j = 0; j < nbr_thread; j++)
	{
		ids[j] = j; 
	}
	thread = malloc(sizeof(pthread_t) * nbr_thread + 1);
	count = atoi(argv[2]);
	pthread_mutex_init(&mutex, NULL);
	for (int j = 0; j < nbr_thread; j++)
		pthread_create(&thread[j], NULL, thread_start, &ids[j]);
	i = 0;
	while (i < nbr_thread)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	pthread_mutex_destroy(&mutex);
	printf("%s%d%s\n", RED, a, RST);
	return (0);
}
