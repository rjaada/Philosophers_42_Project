/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:24:20 by rjaada            #+#    #+#             */
/*   Updated: 2024/08/03 14:08:29 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_death(t_data *data, int i)
{
	long long	current_time;

	current_time = get_time();
	if (current_time - data->philosophers[i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->write_mutex);
		if (!data->someone_died)
		{
			printf("%lld %d died\n", current_time - data->start_time,
				data->philosophers[i].id);
			data->someone_died = 1;
		}
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (data->num_meals == -1)
		return (0);
	while (i < data->num_philosophers)
	{
		if (data->philosophers[i].meals_eaten >= data->num_meals)
			finished_eating++;
		i++;
	}
	return (finished_eating == data->num_philosophers);
}

void	monitoring(t_data *data)
{
	int	i;

	while (!data->someone_died)
	{
		i = 0;
		while (i < data->num_philosophers && !data->someone_died)
		{
			if (check_death(data, i))
				return ;
			if (check_meals(data))
			{
				pthread_mutex_lock(&data->write_mutex);
				printf("All philosophers have eaten enough\n");
				data->someone_died = 1;
				pthread_mutex_unlock(&data->write_mutex);
				return ;
			}
			i++;
		}
		usleep(100);
	}
}
