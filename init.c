/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:00:48 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/05 21:56:12 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit_one(t_data *data, int code)
{
	if (code == 1)
	{
		free(data->fork_mutex);
		free(data);
	}
	else if (code == 2)
	{
		free(data->fork_mutex);
		free(data->forks_philo);
		free(data);
	}
	free(data);
	printf("Error: Allocation failure\n");
	return (EXIT_FAILURE);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philo[i].left_fork = &data->forks_philo[i];
		data->philo[i].l_fork_mutex = &data->fork_mutex[i];
		if (data->philo[i].id == data->nb_philos)
		{
			data->philo[i].right_fork = &data->forks_philo[0];
			data->philo[i].r_fork_mutex = &data->fork_mutex[0];
		}
		else
		{
			data->philo[i].right_fork = &data->forks_philo[i + 1];
			data->philo[i].r_fork_mutex = &data->fork_mutex[i + 1];
		}
		i++;
	}
}

int	init_fork_mutex(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->fork_mutex)
		return (ft_exit_one(data, 0), 0);
	data->forks_philo = malloc(data->nb_philos * sizeof(int));
	if (!data->forks_philo)
		return (ft_exit_one(data, 1), 0);
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philo)
		return (ft_exit_one(data, 2), 0);
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->fork_mutex[i], NULL);
	while (++j < data->nb_philos)
	{
		data->forks_philo[j] = -1;
	}
	return (1);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].status = 0;
		data->philo[i].eating = 0;
		data->philo[i].data = data;
		data->philo[i].time_to_die = 0;
		data->philo[i].dead = 0;
		data->philo[i].last_eat = data->sim_start;
		i++;
	}
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->sim_start = get_time();
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	data->start_time = 0;
	data->eating_done = 0;
	data->any_dead = 0;
	if (!init_fork_mutex(data))
		return (0);
	init_philo(data);
	init_forks(data);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->meals, NULL);
	return (1);
}
