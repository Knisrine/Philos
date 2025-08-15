/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:37:35 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/15 20:31:25 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

pthread_mutex_t *init_forks(int c)
{
	pthread_mutex_t *forks;
	
	forks = malloc(sizeof(pthread_mutex_t) * c);
	if (!forks)
		return NULL;
	int i = 0;
	
	while (i < c)
	{	
		if (pthread_mutex_init(&forks[i++], NULL))
		{
			// destroy reeffs
			free(forks);
			return NULL;
		}
	}
	return forks;
}

void assign_forks(t_data *data)
{
	int i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		i++;
	}
}

int main(int ac, char **av)
{
	t_data *data;
	// t_philo philo;

	data = malloc(sizeof(t_data));

	if (ac != 5 && ac != 6)
		return (printf("5 Or 6 arguments required !! \n"), 1);
	if(!valid_argument(av))
		return (printf("Invalid arguments !! \n"),1);
	if(init_data(data, av))
		return 1;
	data->forks = init_forks(data->nb_philos);
	if(!data->forks)
		return (printf("Failed to initialize forks\n"), 1);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return 1;
	assign_forks(data);
	data->start_time = get_current_time();
	create_threads(data, data->philos);

	int i = 0;
	while (i < data->nb_philos)
		pthread_join(data->philos[i++].thread, NULL);
	// i = 0;
	// while (i < data->nb_philos)
	// {
	// 	pthread_mutex_destroy(&data->philos[i].meal_mutex);
	// 	free(&data->philos[i++].meal_mutex);
	// }
	printf("All philosophers have finished their routines.\n");
	return 0;
} 	