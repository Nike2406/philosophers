/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:53:53 by prochell          #+#    #+#             */
/*   Updated: 2021/08/18 22:31:54 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	p_err(int err)
{
	if (err == 1)
		p_putstr("Incorrect number of arguments!\n");
	if (err == 2)
		p_putstr("Only positive numbers are allowed!\n");
	return(-1);
}

void	p_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	p_limits(long long total, char const s, int sign)
{
	long long	min;
	long long	max;

	max = (total * 10 + (s - '0')) * sign;
	if (max > 2147483647)
		return (-1);
	min = (total * 10 + (s - '0')) * sign;
	if (min < -2147483648)
		return (0);
	return (1);
}

int	p_atoi(const char *str)
{
	int				i;
	int				min;
	long long		total;
	int				lim;

	i = 0;
	min = 1;
	total = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		lim = p_limits(total, str[i], min);
		if (lim < 1)
			return (lim);
		total = (total * 10) + (str[i] - 48);
		i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (total * min);
	}
	return (0);
}

int		check_nums(char **args)
{
	int i;
	int j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
			{
				p_err(2);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

