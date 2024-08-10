/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:00:36 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/05 22:02:23 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num_eat(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meals);
		if (data->philo[i].eat_count >= data->nb_meals)
		{
			pthread_mutex_unlock(&data->meals);
			continue ;
		}
		pthread_mutex_unlock(&data->meals);
		return (0);
	}
	pthread_mutex_lock(&data->dead);
	data->any_dead = 1;
	pthread_mutex_unlock(&data->dead);
	return (1);
}

int	supervisor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->dead);
			if (get_time() - data->philo[i].last_eat > data->time_to_die)
			{
				data->any_dead = 1;
				pthread_mutex_unlock(&data->dead);
				return (data->philo[i].id);
			}
			pthread_mutex_unlock(&data->dead);
			i++;
		}
		if (data->nb_meals != -1 && check_num_eat(data))
			break ;
	}
	return (0);
}

void	*routine(void *pointer)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)pointer;
	data = philo->data;
	if (philo->id % 2 == 0)
	{
		message("is thinking", philo);
		usleep(100);
	}
	while (!is_philo_dead(data))
	{
		if (!take_forks(philo, data))
			break ;
		if (!philo_sleeping(philo, data))
			break ;
		if (!philo_thinking(philo, data))
			break ;
	}
	return ((void *)0);
}

void	join_threads(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->nb_philos)
	{
		if (pthread_join(data->philo[j].tid, 0) != 0)
		{
			printf("Error: pthread_join error\n");
			return ;
		}
	}
}

int	create_threads(t_data *data)
{
	int	i;
	int	id;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philo[i].tid, NULL, &routine, \
		&data->philo[i]))
			return (destory_created_threads(data, i), 0);
		i++;
	}
	id = 0;
	id = supervisor(data);
	if (id != 0)
	{
		pthread_mutex_lock(&data->print);
		printf("%llu %d %s\n", get_time() - data->start_time, id, "died");
		pthread_mutex_unlock(&data->print);
	}
	join_threads(data);
	return (ft_exit(data), 1);
}
