#include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

// Глобальные переменнные
int	mails = 0;
// Глобальная переменная для синхронизации потоков
pthread_mutex_t	mutex;

// Главная функция для подсчета писем
void *routine()
{
	for (long i = 0; i < 1000000; i++)
	{
		// Синхронизация потоков для избежания race condition
		// Происходит посредством встроенного API, где выполнение
		// операции будет только после достижения определенного значения
		// переменной.
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	// Инициализация массива потоков
	pthread_t th[4];
	int	i;
	// Инициализация синхронизации
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		// Создание потока, где
		// 1. th + i - указатель на поток
		// 2. NULL - атрибуты потока
		// 3. &routine - указаетель на исполняемую функцию
		// 4. NULL - аргументы, которые будут переданы функции
		// В случае успешного выполнения ф. возвращается 0
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
			return (-1);
		printf("Thread %d has started.\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		// Ожидание завершения потока
		if (pthread_join(th[i], NULL) != 0)
			return (-1);
		printf("Thread %d has finished execution.\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Mails: %d", mails);
	return (0);
}
