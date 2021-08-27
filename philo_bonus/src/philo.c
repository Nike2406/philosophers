/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:42:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/27 03:57:38 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	create_processes(t_philo **phils, t_data *data)
// {
// 	int			j;
// 	pthread_t	*philo_threads;

// 	j = 0;
// 	data->time = get_time();
// 	philo_threads = malloc(sizeof(pthread_t) * data->num_of_ph);
// 	while (j < data->num_of_ph)
// 	{
// 		if (pthread_create(philo_threads + j, NULL, \
// 				philo_action, phils[j]))
// 			return (-1);
// 		j++;
// 	}
// 	j = 0;
// 	while (j < data->num_of_ph)
// 	{
// 		if (pthread_detach(philo_threads[j]))
// 			return (-1);
// 		j++;
// 	}
// 	// waitress(phils);
// 	free(philo_threads);
// 	philo_destroy(phils, data);
// 	return (0);
// }

void	philo_destroy(t_philo **phils, t_data *data)
{
	int	j;

	sem_close(data->sem);
	j = 0;
	while (j < data->num_of_ph)
	{
		sem_close(phils[j]->fork);
		j++;
	}
}

void	sem_inits(t_data *data)
{
	// t_forks forks;
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("death");
	// sem_unlink("eat_times");
	// data->forks = malloc(sizeof(t_forks));
	data->forks = sem_open("fork", O_CREAT, 0666, data->num_of_ph);
	data->sem = sem_open("message", O_CREAT, 0666, 1);
	data->death = sem_open("death", O_CREAT, 0666, 1);
}

int	philo_phill(t_data *data)
{
	t_philo	**phils;
	int		j;
	// t_forks	*forks;
	int		fd;

	j = 0;
	// data->forks = (t_forks *)malloc(sizeof(t_forks) * data->num_of_ph);
	phils = malloc(sizeof(t_philo *) * data->num_of_ph);
	// data->sem = malloc(sizeof(t_forks));
	sem_inits(data);// pthread_mutex_init(&forks[j], NULL);
	while (j < data->num_of_ph)
	{
		fd = fork();
		if (fd < 0)
			p_err(3);
		data->time = get_time();
		phils[j] = (malloc(sizeof(t_philo) * data->num_of_ph));
		phils[j]->pid = fd;
		if (!fd)
		{
			phils[j]->id = j + 1;
			// pthread_mutex_init(data->mutex, NULL);
			phils[j]->fork = data->forks;
			// phils[j]->right_fork = &forks[(j + 1) % data->num_of_ph];
			phils[j]->data = data;
			if (data->flag_eating_tms)
				phils[j]->is_full = 0;
			// printf("Hi, i am [%d] philo\n", j);
			philo_action(phils[j]);
			exit(0);
		}
		j++;
	}

	j = 0;
	int		status;
	int i = 0;
	while (j < data->num_of_ph)
	{
		// waitpid(-1, 0, 0);
		if (waitpid(-1, &status, 0) < 0)
			p_err(3);
		if (WIFEXITED(status) == 1)
		{
			while (i < data->num_of_ph)
			{
				kill(phils[i]->pid, SIGKILL);
				i++;
			}
		}
		j++;
	}
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
	// data->is_dead = 0;
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
