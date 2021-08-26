#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_NUM 4

sem_t	*sem;

void	*routine(void *args)
{
	printf("Waiting in the login queue %d\n", *(int *)args);
	sem_wait(sem);
	printf("(%d) Logged in\n", *(int *)args);
	sleep(rand() % 5 + 1);
	printf("(%d) Logged out\n", *(int *)args);
	sem_post(sem);
	free(args);
	exit(1);
	return (NULL);
}

int	main()
{
	pthread_t	th[THREAD_NUM];

	// Так как имя семфора становится глобальным,
	// для избежания ошибок сначала отключаем имя семафора
	sem_unlink("thread");
	// Сохраняем в переменную адрес нового семафора
	// 1. Название семафора
	// 2. Метод создания O_CREATE или O_EXCL
	// 3. Доступ для семафора
	// 4. Переменная для начального количества семафоров
	sem = sem_open("thread", O_CREAT, 0666, 1);
	int	i;

	for (i = 0; i < THREAD_NUM; i++)
	{
		int	fd = fork();
		if (!fd)
		{
			int *a = malloc(sizeof(int));
			*a = i;
			routine(a);
		}
	}
	for (i = 0; i < THREAD_NUM; i++)
		waitpid(-1, 0, 0);
	// Закрытие семафора
	sem_close(sem);
	// Отключаем семафор
	sem_unlink("thread");
	return (0);
}
