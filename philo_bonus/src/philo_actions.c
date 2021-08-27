/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:09:42 by prochell          #+#    #+#             */
/*   Updated: 2021/08/27 03:41:12 by prochell         ###   ########.fr       */
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
		usleep(200);
	waitress(tmp);

	while (1)
	{
		take_forks(philo);
		philo_messages(THINKING, get_time() - tmp->data->time, \
			tmp->id, tmp->data->sem);

		// Try to meurder processes
		// int i = 0;
		// while (tmp->data->pid_arr[i])
		// {
		// 	printf("i - %d, pid - %d ", i, tmp->data->pid_arr[i]);
		// 	printf("\n");
		// 	i++;
		// }
	}
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	philo_messages(SLEEPING, get_time() - philo->data->time, \
		philo->id, philo->data->sem);
	p_usleep(philo->data->t_to_sleep);
}

int	eating(t_philo *philo)
{
	// if (philo->data->is_dead)
	// 	exit(1);
	philo_messages(EATING, get_time() - philo->data->time, \
		philo->id, philo->data->sem);
	philo->hungry_time = get_time();
	p_usleep(philo->data->t_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
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
	sem_wait(philo->fork);
	// if (philo->data->is_dead)
	// 	exit(1);
	// printf("Is dead = %d\n", philo->data->is_dead);
	philo_messages(T_L_FORK, get_time() - philo->data->time, \
		philo->id, philo->data->sem);
	sem_wait(philo->fork);
	// if (philo->data->is_dead)
	// 	exit(1);
	philo_messages(T_R_FORK, get_time() - philo->data->time, \
		philo->id, philo->data->sem);
	eating(philo);
}

void	philo_messages(int i, long unsigned int a, int b, t_forks *sem)
{
	sem_wait(sem);
	//pthread_mutex_lock(mutex);
	if (i == T_L_FORK)
		printf("%lu [%d] has taken a fork\n", a, b);
	else if (i == T_R_FORK)
		printf("%lu [%d] has taken a fork\n", a, b);
	else if (i == EATING)
		printf("%lu [%d] \e[0;32mis eating\e[0;39m\n", a, b);
	else if (i == SLEEPING)
		printf("%lu [%d] \e[0;35mis sleeping\e[0;39m\n", a, b);
	else if (i == THINKING)
		printf("%lu [%d] \e[0;33mis thinking\e[0;39m\n", a, b);
	else if (i == DEATH)
	{
		printf("%lu [%d] \e[0;31mdied\e[0;39m\n", a, b);
		// int j = 0;
		// while (j < philo)
		// kill(0, SIGKILL);
		exit(1);
	}
	sem_post(sem);
	// pthread_mutex_unlock(mutex);
}

void philo_death(long unsigned int a, int b, t_forks *sem)
{
	sem_wait(sem);
	printf("%lu [%d] \e[0;31mdied\e[0;39m\n", a, b);
	sem_post(sem);
	exit(1);
}
