/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:42:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/22 13:51:03 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	*some_func()
{
	printf("Philo works\n");
	return (NULL);
}

int	philo_phill(t_data *philo)
{
	unsigned int	i;
	pthread_t		philo_threads[philo->num_of_ph];

	i = 0;
	pthread_mutex_init(&(philo->mutex), NULL);
	while (i < philo->num_of_ph)
	{
		if (pthread_create(philo_threads + i, NULL, &some_func, NULL))
			return (-1);
		i++;
	}
	i = 0;
	while (i < philo->num_of_ph)
	{
		if (pthread_join(philo_threads[i], NULL))
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&(philo->mutex));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	philo;

	if (argc != 5 && argc != 6)
		return(p_err(1));
	if (check_nums(argv) < 0)
		return (-1);
	philo.num_of_ph = p_atoi(argv[1]);
	philo.t_to_die = p_atoi(argv[2]);
	philo.t_to_eat = p_atoi(argv[3]);
	philo.t_to_sleep = p_atoi(argv[4]);
	if (argc == 6)
		philo.ph_m_to_eat = p_atoi(argv[5]);
	philo_phill(&philo);

	// if ((t_philo *)malloc(sizeof(t_philo) * philo.num_of_ph) == 0)
	// 	return (-1);

	// pthread_t	p1, p2;
	// pthread_create(&p1, NULL, &some_func, NULL);
	// pthread_create(&p2, NULL, &some_func, NULL);
	// pthread_join(p1, NULL);
	// pthread_join(p2, NULL);

	return (0);
}
