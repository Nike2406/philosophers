/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:09:42 by prochell          #+#    #+#             */
/*   Updated: 2021/08/23 20:32:26 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_action(void *philo)
{
	t_philo *tmp;
	tmp = philo;
	tmp->hungry_time = get_time();
	tmp->eat_count = 0;
	if (!(tmp->id % 2))
		usleep(100);
	long i = 0;
	while (i < 10)
	{
		if (is_dead(philo) < 0)
			return (NULL);
		if (take_forks(philo) < 0)
			return (NULL);
		if (thinking(philo) < 0)
			return (NULL);
		i++;
	}
	usleep(100);
	return (NULL);
}

int	thinking(t_philo *philo)
{
	if (is_dead(philo) < 0)
		return (-1);
	printf("%d [%d] \e[0;33mis thinking\e[0;39m\n", get_time() \
		- philo->data->time, philo->id);
	return (0);
}

int	is_dead(t_philo *philo)
{
	if ((get_time() - philo->hungry_time) > philo->data->t_to_die)
	{
		printf("%d [%d] \e[0;31mis dead\e[0;39m\n", get_time() \
		- philo->data->time, philo->id);
		return (-1);
	}
	return (0);
}

void	sleeping(t_philo *philo)
{
	printf("%d [%d] \e[0;35mis sleeping\e[0;39m\n", get_time() \
		- philo->data->time, philo->id);
	usleep(philo->data->t_to_sleep * 1000);
}

int	eating(t_philo *philo)
{
	printf("%d [%d] \e[0;32mis eating\e[0;39m\n", get_time() \
		- philo->data->time, philo->id);
	philo->hungry_time = get_time();
	usleep(philo->data->t_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->data->flag_eating_tms)
		philo->eat_count++;
	if (philo->data->flag_eating_tms && (philo->eat_count >= philo->data->ph_m_to_eat))
		return (-1);
	sleeping(philo);
	return (0);
}

int	take_forks(t_philo *philo)
{
	printf("%d [%d] has taken a fork\n", get_time() - philo->data->time, philo->id);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("%d [%d] has taken a fork\n", get_time() - philo->data->time, philo->id);
	if (eating(philo) < 0)
		return (-1);
	return (0);
}
