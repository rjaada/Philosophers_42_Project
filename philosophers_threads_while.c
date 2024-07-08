#include <pthread.h> // Hadi hiya l-library li khedemha bash nkhedmo b threads
#include <stdio.h>
#include <unistd.h> // Hadi bash nkhedmo b sleep()

// Hadi hiya l-function li ghadi tkoun executed by kol thread
void	*philosopher_routine(void *arg)
{
	int id = *(int *)arg;
		// Kan7ewlo l-argument l int bash n3erfo philosopher number
	for (int i = 0; i < 5; i++)
	{                                              
		// Kol philosopher ghadi yakol o yfeker 5 marrat
		printf("Philosopher %d is thinking\n", id);
			// Kanaffchiw bli l-philosopher kayfeker
		sleep(1);                                  
			// Kansimulliw l-wa9t li kayfeker fih (1 second)
		printf("Philosopher %d is eating\n", id);
			// Kanaffchiw bli l-philosopher kayakol
		sleep(1);                                
			// Kansimulliw l-wa9t li kayakol fih (1 second)
	}
	return (NULL); // Khas kol pthread function trejje3 pointer (NULL hna)
}

int	main(void)
{
	pthread_t threads[5];
		// Kan3erfo array dyal 5 threads (wa7ed lkol philosopher)
	int ids[5];           // Array dyal IDs dyal l-philosophers
	// Hna kancrééyiw 5 threads, wa7ed lkol philosopher
	for (int i = 0; i < 5; i++)
	{
		ids[i] = i + 1; // Kan3tiw ID lkol philosopher (1 to 5)
		// pthread_create kay-créer thread jdid
		// &threads[i]: fin ghadi nstockiw l-thread
		// NULL: default thread attributes
		// philosopher_routine: l-function li ghadi texecuta f had thread
		// &ids[i]: l-argument li ghanmrerro l philosopher_routine
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&ids[i]) != 0)
		{
			printf("Error creating thread\n");
			return (1);
		}
	}
	// Hna kantsennaw gaa3 l-threads ysaliw
	for (int i = 0; i < 5; i++)
	{
		pthread_join(threads[i], NULL); // pthread_join kaytsenna thread ysali
	}
	return (0);
}
