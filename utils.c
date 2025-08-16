/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:16:24 by nikhtib           #+#    #+#             */
/*   Updated: 2025/08/16 22:44:40 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(int c)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * c);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < c)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
		{
			// destroy_mutex(forks);
			free(forks);
			return (NULL);
		}
	}
	return (forks);
}

void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		i++;
	}
}

void	wait_treads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
		pthread_join(data->philos[i++].thread, NULL);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
}
