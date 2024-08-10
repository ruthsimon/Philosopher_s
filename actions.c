/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:56:24 by mkiflema          #+#    #+#             */
/*   Updated: 2024/08/06 17:26:54 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eating(t_philo *philo, t_data *data)
{
	if (is_philo_dead(data))
		return (drop_forks(philo), 0);
	message("is eating", philo);
	pthread_mutex_lock(&philo->data->dead);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->dead);
	if (is_philo_dead(data))
		return (drop_forks(philo), 0);
	ft_usleep(philo->data->time_to_eat, data);
	pthread_mutex_lock(&philo->data->meals);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meals);
	drop_forks(philo);
	return (1);
}

int	philo_sleeping(t_philo *philo, t_data *data)
{
	if (!is_philo_dead(data))
	{
		message("is sleeping", philo);
		ft_usleep(data->time_to_sleep, data);
		return (1);
	}
	return (0);
}

int	philo_thinking(t_philo *philo, t_data *data)
{
	if (!is_philo_dead(data))
	{
		message("is thinking", philo);
		return (1);
	}
	return (0);
}

int	ft_usleep(unsigned long long time, t_data *data)
{
	unsigned long long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (is_philo_dead(data))
			return (0);
		usleep(200);
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->meals);
	free(data->philo);
	free(data->forks_philo);
	free(data->fork_mutex);
	free(data);
	return ;
}
