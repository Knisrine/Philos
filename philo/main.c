/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:37:35 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/17 15:44:17 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (ac != 5 && ac != 6)
		return (print_error(2, "5 Or 6 arguments required !! \n"), 1);
	if (!valid_argument(av))
		return (print_error(2, "Invalid arguments !! \n"), 1);
	if (init_data(data, av)) 
		return (1);
	data->forks = init_forks(data->nb_philos);
	if (!data->forks)
		return (free (data), print_error(2, "Failed to initialize forks\n"), 1);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	assign_forks(data);
	data->start_time = get_current_time();
	create_threads(data, data->philos);
	wait_treads(data);
	destroy_mutex(data);
	free (data);
	return (0);
}
