/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:52:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/24 20:07:56 by prochell         ###   ########.fr       */
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

# define T_L_FORK	1
# define T_R_FORK	2
# define EATING		3
# define SLEEPING	4
# define THINKING	5
# define DEATH		6

typedef pthread_mutex_t	t_forks;
typedef struct s_data
{
	unsigned int	num_of_ph;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	ph_m_to_eat;
	unsigned int	time;
	unsigned int	flag_eating_tms;
	unsigned int	is_full;
	t_forks			*mutex;
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
int		get_time(void);
void	p_usleep(long long time);

int		philo_phill(t_data *philo);
void	*philo_action(void *data);
void	philo_messages(int i, unsigned int a, unsigned int b, t_forks *mutex);
void	philo_destroy(t_philo **phils, t_data *data);

int		waitress(t_philo **phils);
void	*check_philo(void *phils);

void	take_forks(t_philo *philo);
int		eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

#endif
