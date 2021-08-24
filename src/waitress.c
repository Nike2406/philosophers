/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:41:29 by prochell          #+#    #+#             */
/*   Updated: 2021/08/24 15:52:50 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	waitress(t_philo **phils)
{
	pthread_t	waitress;

	if (pthread_create(&waitress, NULL, check_philo, (void *)phils))
		return (-1);
	if (pthread_join(waitress, NULL))
		return (-1);
	return (0);
}

void	*check_philo(void *phils)
{
	unsigned int	i;
	t_philo			**tmp;

	tmp = (t_philo **)phils;
	i = 0;
	while (1)
	{
		if (i >= tmp[0]->data->num_of_ph)
			i = 0;
		if ((tmp[i]->eat_count >= tmp[0]->data->ph_m_to_eat) && tmp[0]->data->flag_eating_tms)
			{
				tmp[0]->data->is_full++;
				if (tmp[0]->data->is_full < tmp[0]->data->num_of_ph)
				{
					i++;
					continue;
				}
				else
					return (NULL);
			}
		// printf("Time %d, philo %d\n", (get_time() - tmp[i]->hungry_time), tmp[i]->id);
		if ((get_time() - tmp[i]->hungry_time) > tmp[i]->data->t_to_die)
		{
			// pthread_mutex_lock();
			philo_messages(DEATH, get_time() - tmp[i]->data->time, tmp[i]->id, tmp[0]->data->mutex);
			return ((void *)-1);
		}
		i++;
		usleep(100);
	}
	return (NULL);
}
