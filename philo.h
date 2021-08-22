/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:52:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/22 16:24:13 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h> // memset
# include <sys/time.h>

typedef struct s_data
{
	unsigned int	num_of_ph;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	ph_m_to_eat;
	pthread_mutex_t	mutex;
}	t_data;

typedef struct s_philo
{
	pthread_t		ph;
	unsigned int	id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data			*data;
}	t_philo;


int		p_err(int err);
void	p_putstr(char *str);
int		p_limits(long long total, char const s, int sign);
int		p_atoi(const char *str);
int		check_nums(char **args);

int		philo_phill(t_data *philo);
void	*philo_action(void *data);

#endif
