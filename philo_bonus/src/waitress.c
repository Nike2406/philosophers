/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:41:29 by prochell          #+#    #+#             */
/*   Updated: 2021/08/27 03:55:42 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	waitress(t_philo *philo)
{
	pthread_t	waitress;

	waitress = malloc(sizeof(pthread_t));
	if (pthread_create(&waitress, NULL, check_philo, (void *)philo))
		return (-1);
	if (pthread_detach(waitress))
		return (-1);
	return (0);
}

void	*check_philo(void *phils)
{
	int		i;
	t_philo	*tmp;

	tmp = (t_philo *)phils;
	i = 0;
	while (1)
	{
		if (i >= tmp->data->num_of_ph)
			i = 0;
		// if (check_fullfillment(tmp) < 0)
		// 	return (NULL);
		if ((get_time() - tmp->hungry_time) > tmp->data->t_to_die)
		{
			// tmp->data->is_dead = 1;
			philo_death(get_time() - tmp->data->time, tmp->id, \
				tmp->data->sem);
			// return ((void *) -1);
			exit (1);
		}
		i++;
		usleep(100);
	}
	return (NULL);
}

// int	check_fullfillment(t_philo *tmp)
// {
// 	int	j;
// 	int	fullfillment;

// 	j = 0;
// 	fullfillment = 0;
// 	while ((j < tmp[0]->data->num_of_ph) && tmp[0]->data->flag_eating_tms)
// 		fullfillment += tmp[j++]->is_full;
// 	if ((fullfillment >= tmp[0]->data->num_of_ph) \
// 		&& tmp[0]->data->flag_eating_tms)
// 		return (-1);
// 	return (0);
// }
