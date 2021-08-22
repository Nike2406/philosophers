/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:09:42 by prochell          #+#    #+#             */
/*   Updated: 2021/08/22 16:24:59 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_action(void *data)
{
	t_philo *tmp;
	tmp = data;
	// (void)data;
	// while (1)
	// {
	// 	think();
	// 	take_forks();
	// 	eat();
	// 	put_forks();
	// }
	printf("I am %d philosopher\n", tmp->id);
	usleep(100);
	return (NULL);
}
