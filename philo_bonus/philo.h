/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:52:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/27 03:39:14 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

# define T_L_FORK	1
# define T_R_FORK	2
# define EATING		3
# define SLEEPING	4
# define THINKING	5
# define DEATH		6

typedef sem_t	t_forks;
typedef struct s_data
{
	int	num_of_ph;
	long unsigned int	t_to_die;
	long unsigned int	t_to_eat;
	long unsigned int	t_to_sleep;
	int	ph_m_to_eat;
	long unsigned int	time;
	int		flag_eating_tms;
	// int		is_dead;
	t_forks	*sem;
	t_forks	*death;
	t_forks	*forks;
}	t_data;

typedef struct s_philo
{
	int		id;
	t_data	*data;
	int		status;
	long unsigned int	hungry_time;
	int		eat_count;
	int		is_full;
	t_forks	*fork;
	int		pid;
}	t_philo;

int		p_err(int err);
int		p_limits(long long total, char const s, int sign);
int		p_atoi(const char *str);
int		check_nums(char **args);
long unsigned int	get_time(void);
void	p_usleep(long long time);

int		data_fill(int argc, char **argv, t_data *data);
int		philo_phill(t_data *philo);
void	*philo_action(void *data);
void	philo_messages(int i, long unsigned int a, int b, t_forks *sem);
void	philo_destroy(t_philo **phils, t_data *data);
int		create_processes(t_philo **phils, t_data *data);

int		waitress(t_philo *philo);
void	*check_philo(void *phils);
int		check_fullfillment(t_philo **tmp);

void	take_forks(t_philo *philo);
int		eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	philo_death(long unsigned int a, int b, t_forks *sem);

void	sem_inits(t_data *data);

#endif
