/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:16:24 by nikhtib           #+#    #+#             */
/*   Updated: 2025/08/17 15:42:45 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(int ms)
{
	int	start;

	start = get_current_time();
	while (get_current_time() - start < ms)
		usleep(200);
}

pthread_mutex_t	*init_forks(int n)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
		{
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
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				i;

	i = 0;
	forks = data->forks;
	philos = data->philos;
	wait_treads(data);
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(philos[i].right_fork);
		pthread_mutex_destroy(philos[i].left_fork);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->philos_ate_mutex);
	pthread_mutex_destroy(&data->count_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->max_meal);
	free(forks);
	free(philos);
}
