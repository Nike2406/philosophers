/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:42:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/21 21:39:38 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	*some_func()
{
	printf("Here is a function\n");
	return (NULL);
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

	// if ((t_philo *)malloc(sizeof(t_philo) * philo.num_of_ph) == 0)
	// 	return (-1);

	// pthread_t	p1, p2;
	// pthread_create(&p1, NULL, &some_func, NULL);
	// pthread_create(&p2, NULL, &some_func, NULL);
	// pthread_join(p1, NULL);
	// pthread_join(p2, NULL);

	return (0);
}
