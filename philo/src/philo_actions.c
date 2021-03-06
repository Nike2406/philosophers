/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:09:42 by prochell          #+#    #+#             */
/*   Updated: 2021/08/24 22:50:44 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_action(void *philo)
{
	t_philo	*tmp;

	tmp = philo;
	tmp->hungry_time = get_time();
	tmp->eat_count = 0;
	if (!(tmp->id % 2))
		usleep(100);
	while (1)
	{
		take_forks(philo);
		philo_messages(THINKING, get_time() - tmp->data->time, \
			tmp->id, tmp->data->mutex);
	}
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	philo_messages(SLEEPING, get_time() - philo->data->time, \
		philo->id, philo->data->mutex);
	p_usleep(philo->data->t_to_sleep);
}

int	eating(t_philo *philo)
{
	philo_messages(EATING, get_time() - philo->data->time, \
		philo->id, philo->data->mutex);
	philo->hungry_time = get_time();
	p_usleep(philo->data->t_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->data->flag_eating_tms)
	{
		philo->eat_count++;
		if (philo->eat_count >= philo->data->ph_m_to_eat)
			philo->is_full = 1;
	}
	sleeping(philo);
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_messages(T_L_FORK, get_time() - philo->data->time, \
		philo->id, philo->data->mutex);
	pthread_mutex_lock(philo->right_fork);
	philo_messages(T_R_FORK, get_time() - philo->data->time, \
		philo->id, philo->data->mutex);
	eating(philo);
}

void	philo_messages(int i, int a, int b, t_forks *mutex)
{
	pthread_mutex_lock(mutex);
	if (i == T_L_FORK)
		printf("%d [%d] has taken a fork\n", a, b);
	else if (i == T_R_FORK)
		printf("%d [%d] has taken a fork\n", a, b);
	else if (i == EATING)
		printf("%d [%d] \e[0;32mis eating\e[0;39m\n", a, b);
	else if (i == SLEEPING)
		printf("%d [%d] \e[0;35mis sleeping\e[0;39m\n", a, b);
	else if (i == THINKING)
		printf("%d [%d] \e[0;33mis thinking\e[0;39m\n", a, b);
	else if (i == DEATH)
	{
		printf("%d [%d] \e[0;31mdied\e[0;39m\n", a, b);
		return ;
	}
	pthread_mutex_unlock(mutex);
}
