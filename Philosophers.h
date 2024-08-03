/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:24:41 by rjaada            #+#    #+#             */
/*   Updated: 2024/08/03 14:08:49 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	t_philosopher	*philosophers;
}					t_data;

// init.c
int					init_data(t_data *data);

// utils.c
int					ft_atoi(const char *str);
long long			get_time(void);
void				ft_usleep(long long time);

// philosophers.c
void				print_status(t_philosopher *philo, char *status);
int					create_threads(t_data *data);
void				cleanup(t_data *data);
void				philosopher_cycle(t_philosopher *philo);

// monitoring.c
void				monitoring(t_data *data);

#endif