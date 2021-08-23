/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:52:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/23 20:44:08 by prochell         ###   ########.fr       */
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

// # define HUNGRY 0
// # define FULL 1

typedef pthread_mutex_t t_forks;
typedef struct s_data
{
	unsigned int	num_of_ph;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	ph_m_to_eat;
	unsigned int	time;
	unsigned int	flag_eating_tms;
}	t_data;

typedef struct s_philo
{
	unsigned int	id;
	t_forks			*left_fork;
	t_forks			*right_fork;
	t_data			*data;
	unsigned int	status;
	unsigned int	hungry_time;
	unsigned int	eat_count;
}	t_philo;

int		p_err(int err);
int		p_limits(long long total, char const s, int sign);
int		p_atoi(const char *str);
int		check_nums(char **args);
int		get_time();

int		philo_phill(t_data *philo);
void	*philo_action(void *data);

int		waitress(t_philo **phils);
void	check_philo(t_philo **phils);

int		take_forks(t_philo *philo);
int		eating(t_philo *philo);
void	sleeping(t_philo *philo);
int		is_dead(t_philo *philo);
int		thinking(t_philo *philo);

#endif
