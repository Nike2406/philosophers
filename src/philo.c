/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:42:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/24 15:42:12 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

int	create_threads(t_philo **phils, t_data *data)
{
	unsigned int	j;
	pthread_t		philo_threads[data->num_of_ph];

	j = 0;
	data->time  = get_time();

	while (j < data->num_of_ph)
	{
		if (pthread_create(philo_threads + j, NULL,
			philo_action, phils[j]))
			return (-1);
		j++;
		// usleep(100);
	}
	j = 0;
	while (j < data->num_of_ph)
	{
		if (pthread_detach(philo_threads[j]))
			return (-1);
		j++;
	}
	waitress(phils);
	pthread_mutex_destroy(data->mutex);
	j = 0;
	while (j < data->num_of_ph)
	{
		pthread_mutex_destroy(phils[j]->left_fork);
		j++;
	}
	return (0);
}

int	philo_phill(t_data *data)
{
	t_philo 		**phils;
	unsigned int	j;
	t_forks			*forks;

	j = 0;
	forks = (t_forks *)malloc(sizeof(t_forks) * data->num_of_ph);
	phils = malloc(sizeof(t_philo *) * data->num_of_ph);
	data->mutex = malloc(sizeof(t_forks));
	while (j < data->num_of_ph)
	{
		phils[j] = (malloc(sizeof(t_philo) * data->num_of_ph));
		phils[j]->id = j + 1;
		pthread_mutex_init(&forks[j], NULL);
		pthread_mutex_init(data->mutex, NULL);
		phils[j]->left_fork = &forks[j];
		phils[j]->right_fork = &forks[(j + 1) % data->num_of_ph];
		phils[j]->data = data;
		j++;
	}
	if (create_threads(phils, data) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return(p_err(1));
	if (check_nums(argv) < 0)
		return (-1);
	data.num_of_ph = p_atoi(argv[1]);
	data.t_to_die = p_atoi(argv[2]);
	data.t_to_eat = p_atoi(argv[3]);
	data.t_to_sleep = p_atoi(argv[4]);
	if (argc == 6)
	{
		data.ph_m_to_eat = p_atoi(argv[5]);
		if (data.ph_m_to_eat < 1)
			return (-1);
		data.flag_eating_tms = 1;
		data.is_full = 0;
	}
	else
		data.flag_eating_tms = 0;
	if (philo_phill(&data) < 0)
		return (-1);
	return (0);
}
