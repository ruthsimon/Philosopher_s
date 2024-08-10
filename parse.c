/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:26:57 by mkiflema          #+#    #+#             */
/*   Updated: 2024/08/05 22:02:12 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destory_created_threads(t_data *data, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		pthread_detach(data->philo[i].tid);
		i++;
	}
	return (0);
}

int	validate_numerical_string(const char *str)
{
	int	j;

	j = 0;
	while (str && str[j] && str[j] == ' ')
		j++;
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
		{
			ft_putstr_fd("Ensure inputs are numerical/positive!\n", 2);
			return (0);
		}
		j++;
	}
	return (1);
}

int	parse(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) <= 0)
		{
			if (ft_atoi(argv[i]) > INT_MAX)
				ft_putstr_fd("Input should be below int max\n", 2);
			else
				ft_putstr_fd("Input should be + or > 0\n", 2);
			return (0);
		}
		if (!validate_numerical_string(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
