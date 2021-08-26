/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:42:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/26 15:54:16 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_philo **phils, t_data *data)
{
	int			j;
	pthread_t	*philo_threads;

	j = 0;
	data->time = get_time();
	philo_threads = malloc(sizeof(pthread_t) * data->num_of_ph);
	while (j < data->num_of_ph)
	{
		if (pthread_create(philo_threads + j, NULL, \
				philo_action, phils[j]))
			return (-1);
		j++;
	}
	j = 0;
	while (j < data->num_of_ph)
	{
		if (pthread_detach(philo_threads[j]))
			return (-1);
		j++;
	}
	waitress(phils);
	free(philo_threads);
	philo_destroy(phils, data);
	return (0);
}

void	philo_destroy(t_philo **phils, t_data *data)
{
	int	j;

	pthread_mutex_destroy(data->mutex);
	j = 0;
	while (j < data->num_of_ph)
	{
		pthread_mutex_destroy(phils[j]->left_fork);
		j++;
	}
}

void	sem_inits(t_philo	*philo, t_data *data)
{
	sem_unlink("forks");
	sem_unlink("message");
	// sem_unlink("death");
	// sem_unlink("eat_times");
	philo->left_fork = sem_open("forks", O_CREAT, 0777, 1);
	sem_open("message", O_CREAT, 0777, 1);
}

int	philo_phill(t_data *data)
{
	t_philo	**phils;
	int		j;
	t_forks	*forks;

	j = 0;
	forks = (t_forks *)malloc(sizeof(t_forks) * data->num_of_ph);
	phils = malloc(sizeof(t_philo *) * data->num_of_ph);
	data->mutex = malloc(sizeof(t_forks));
	while (j < data->num_of_ph)
	{
		phils[j] = (malloc(sizeof(t_philo) * data->num_of_ph));
		phils[j]->id = j + 1;
		sem_inits(phils[j], data);// pthread_mutex_init(&forks[j], NULL);
		// pthread_mutex_init(data->mutex, NULL);
		// phils[j]->left_fork = &forks[j];
		// phils[j]->right_fork = &forks[(j + 1) % data->num_of_ph];
		phils[j]->data = data;
		if (data->flag_eating_tms)
			phils[j]->is_full = 0;
		j++;
	}
	if (create_threads(phils, data) < 0)
		return (-1);
	free(phils);
	return (0);
}

int	data_fill(int argc, char **argv, t_data *data)
{
	data->num_of_ph = p_atoi(argv[1]);
	if (data->num_of_ph < 1)
		return (-1);
	data->t_to_die = p_atoi(argv[2]);
	data->t_to_eat = p_atoi(argv[3]);
	data->t_to_sleep = p_atoi(argv[4]);
	if (argc == 6)
	{
		data->ph_m_to_eat = p_atoi(argv[5]);
		if (data->ph_m_to_eat < 1)
			return (-1);
		data->flag_eating_tms = 1;
	}
	else
		data->flag_eating_tms = 0;
	if (data->num_of_ph < 0 || data->t_to_die < 0 || \
		data->t_to_eat < 0 || data->t_to_sleep < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (p_err(1));
	if (check_nums(argv) < 0)
		return (-1);
	if (data_fill(argc, argv, &data) < 0)
		return (p_err(2));
	if (philo_phill(&data) < 0)
		return (-1);
	return (0);
}
