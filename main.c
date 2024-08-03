/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:24:07 by rjaada            #+#    #+#             */
/*   Updated: 2024/08/03 14:07:54 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	parse_arguments(int argc, char *argv[], t_data *data)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_meals = -1;
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	if (data->num_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6
			&& data->num_meals <= 0))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parse_arguments(argc, argv, &data))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_data(&data))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	if (create_threads(&data))
	{
		printf("Error: Thread creation failed\n");
		return (1);
	}
	monitoring(&data);
	cleanup(&data);
	return (0);
}
