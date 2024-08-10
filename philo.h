/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:57:01 by mkiflema          #+#    #+#             */
/*   Updated: 2024/08/06 20:36:35 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H_
#define PHILO_H_

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	int					status;
	int					dead;
	unsigned long long	time_to_die;
	unsigned long long	last_eat;
	pthread_mutex_t		*r_fork_mutex;
	pthread_mutex_t		*l_fork_mutex;
	int					*right_fork;
	int					*left_fork;
	t_data				*data;
	pthread_t			tid;
	int					eating;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					nb_meals;
	int					any_dead;
	unsigned long long	sim_start;
	unsigned long long	start_time;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	t_philo				*philo;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		dead;
	pthread_mutex_t		print;
	pthread_mutex_t		eat;
	pthread_mutex_t		meals;
	int					eating_done;
	int					*forks_philo;
}	t_data;

//main.c
int			error_msg(char *msg, t_data *data);
//init.c
int			parse(char **argv);
int			init_data(int argc, char **argv, t_data *data);
//utils.c
long long	ft_atoi(const char *str);
u_int64_t	get_time(void);
int			ft_strcmp(char *s1, char *s2);
int			ft_usleep(unsigned long long time, t_data *data);
void		ft_exit(t_data *data);
void		ft_putstr_fd(char *s, int fd);
//threads.c
int			create_threads(t_data *data);
int			case_one(t_data *data);
void		message(char *str, t_philo *philo);
void		drop_forks(t_philo *philo);
//tasks.c
int			is_philo_dead(t_data *data);
int			take_forks(t_philo *philo, t_data *data);
int			philo_eating(t_philo *philo, t_data *data);
int			philo_sleeping(t_philo *philo, t_data *data);
int			philo_thinking(t_philo *philo, t_data *data);
int			check_num_eat(t_data *data);
int			parse(char **argv);

//parse.c
int			destory_created_threads(t_data *data, int c);

#endif