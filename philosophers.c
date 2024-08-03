/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:24:32 by rjaada            #+#    #+#             */
/*   Updated: 2024/08/03 14:08:42 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_status(t_philosopher *philo, char *status)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->someone_died)
	{
		current_time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", current_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->data->num_philosophers == 1)
	{
		print_status(philo, "has taken a fork");
		return (ft_usleep(philo->data->time_to_die), NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo->data->someone_died && (philo->data->num_meals == -1
			|| philo->meals_eaten < philo->data->num_meals))
		philosopher_cycle(philo);
	return (NULL);
}

void	philosopher_cycle(t_philosopher *philo)
{
	print_status(philo, "is thinking");
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i
				+ 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	free(data->forks);
	free(data->philosophers);
}
