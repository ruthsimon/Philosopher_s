/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:00:19 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/06 20:23:42 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo.h"

int	is_fork_available(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork_mutex);
	if (*philo->left_fork && *philo->left_fork != philo->id)
		pthread_mutex_unlock(philo->l_fork_mutex);
	else
		return (pthread_mutex_unlock(philo->l_fork_mutex), 0);
	pthread_mutex_lock(philo->r_fork_mutex);
	if (*philo->right_fork && *philo->right_fork != philo->id)
		pthread_mutex_unlock(philo->r_fork_mutex);
	else
		return (pthread_mutex_unlock(philo->r_fork_mutex), 0);
	return (1);
}

int	philo_took_fork(t_philo *philo)
{
	if (!is_fork_available(philo))
		return (0);
	pthread_mutex_lock(philo->l_fork_mutex);
	*philo->left_fork = 0;
	pthread_mutex_unlock(philo->l_fork_mutex);
	pthread_mutex_lock(philo->r_fork_mutex);
	*philo->right_fork = 0;
	pthread_mutex_unlock(philo->r_fork_mutex);
	message("has taken a fork", philo);
	message("has taken a fork", philo);
	return (1);
}

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (is_philo_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	printf ("%llu %d %s\n", get_time() - philo->data->start_time, \
		philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	take_forks(t_philo *philo, t_data *data)
{
	if (is_philo_dead(data))
		return (0);
	while (!philo_took_fork(philo))
	{
		usleep(100);
		if (is_philo_dead(data))
			return (0);
	}
	if (!philo_eating(philo, data))
		return (0);
	return (1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork_mutex);
	*philo->right_fork = philo->id;
	pthread_mutex_unlock(philo->r_fork_mutex);
	pthread_mutex_lock(philo->l_fork_mutex);
	*philo->left_fork = philo->id;
	pthread_mutex_unlock(philo->l_fork_mutex);
}
