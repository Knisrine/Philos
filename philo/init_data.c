/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 01:36:11 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/17 22:42:24 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo)
{
	philo->count_meals = 0;
	pthread_mutex_init(&philo->meal_mutex, NULL);
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		if (init_philo(&data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->nb_philos = small_atoi(av[1]);
	data->t_die = small_atoi(av[2]);
	data->t_eat = small_atoi(av[3]);
	data->t_sleep = small_atoi(av[4]);
	data->start_time = get_current_time();
	data->nb_must_eat = -1;
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->count_mutex, NULL);
	if (av[5])
		data->nb_must_eat = small_atoi(av[5]);
	if (create_philos(data))
		return (1);
	return (0);
}
