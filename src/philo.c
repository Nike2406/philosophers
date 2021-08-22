/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:42:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/22 16:26:57 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

// int	create_threads()

int	philo_phill(t_data *data)
{
	pthread_t		philo_threads[data->num_of_ph];

	unsigned int j = 0;
	t_philo **phils;
	phils = malloc(sizeof(t_philo *) * data->num_of_ph);
	while (j < data->num_of_ph)
	{
		phils[j] = (malloc(sizeof(t_philo) * data->num_of_ph));
		phils[j]->id = j + 1;
		j++;
	}

	j = 0;
	pthread_mutex_init(&(data->mutex), NULL);
	while (j < data->num_of_ph)
	{
		if (pthread_create(philo_threads + j, NULL,
			philo_action, phils[j]))
			return (-1);
		j++;
		usleep(100);
	}
	j = 0;
	while (j < data->num_of_ph)
	{
		if (pthread_join(philo_threads[j], NULL))
			return (-1);
		j++;
	}
	pthread_mutex_destroy(&(data->mutex));
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
		data.ph_m_to_eat = p_atoi(argv[5]);
	else
		data.ph_m_to_eat = 0;
	philo_phill(&data);

	// if ((t_philo *)malloc(sizeof(t_philo) * philo.num_of_ph) == 0)
	// 	return (-1);

	// pthread_t	p1, p2;
	// pthread_create(&p1, NULL, &some_func, NULL);
	// pthread_create(&p2, NULL, &some_func, NULL);
	// pthread_join(p1, NULL);
	// pthread_join(p2, NULL);

	return (0);
}
