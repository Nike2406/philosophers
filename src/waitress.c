/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:41:29 by prochell          #+#    #+#             */
/*   Updated: 2021/08/23 20:44:02 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	waitress(t_philo **phils)
{
	pthread_t	waitress;

	if (pthread_create(&waitress, NULL,
			philo_action, phils))
			return (-1);
	if (pthread_join(waitress, NULL))
			return (-1);
	return (0);
}

void	check_philo(t_philo **phils)
{

}
