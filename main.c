/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:00:45 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/06 20:36:59 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo.h"

int	is_philo_dead(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->dead);
	res = data->any_dead;
	pthread_mutex_unlock(&data->dead);
	return (res);
}

int	case_one(t_data *data)
{
	data->start_time = get_time();
	pthread_mutex_lock(&data->meals);
	message("has taken a fork", data->philo);
	pthread_mutex_unlock(&data->meals);
	ft_usleep(data->time_to_die, data);
	pthread_mutex_lock(&data->meals);
	message("died", data->philo);
	pthread_mutex_unlock(&data->meals);
	ft_exit(data);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	error_msg(char *msg, t_data *data)
{
	if (data)
		ft_exit(data);
	write(1, msg, ft_strlen(msg));
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Wrong num of inputs\n", 2), 0);
	if (!parse(argv))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!init_data(argc, argv, data))
		return (1);
	if (data->nb_philos == 1)
		return (case_one(data), 0);
	if (!create_threads(data))
		return (error_msg("Thread for philos failed\n", data), 0);
	return (1);
}
