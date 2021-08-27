/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:29:26 by prochell          #+#    #+#             */
/*   Updated: 2021/08/26 22:51:28 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	p_err(int err)
{
	if (err == 1)
		printf("Incorrect number of arguments!\n");
	else if (err == 2)
		printf("Only positive and not overwelming numbers are allowed!\n");
	else if (err == 3)
		printf("Fork error\n");
	exit(1);
}
