/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:43:12 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/17 15:36:11 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_dead_flag(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->data->death_mutex);
	flag = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (flag);
}

void	check_dead(t_philo *philo)
{
	int	i;
	int	time;

	i = 0;
	while (!get_dead_flag(philo) && i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		time = get_current_time() - philo->t_last_meal;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (time > philo->data->t_die)
		{
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->dead_flag = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			status(philo, RED, "died");
			break ;
		}
		i++;
	}
	if (philo->data->nb_must_eat != -1 && check_nb_meals(philo))
		return ;
}

int	check_nb_meals(t_philo *philo)
{
	int		i;
	int		count;
	t_data	*data;
	t_philo	*philos;

	data = philo->data;
	philos = data->philos;
	i = 0;
	count = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->count_mutex);
		if (data->philos[i].count_meals >= data->nb_must_eat)
			count++;
		pthread_mutex_unlock(&data->count_mutex);
		if (count == data->nb_philos)
		{
			pthread_mutex_lock(&data->philos_ate_mutex);
			data->philos_ate = 1;
			pthread_mutex_unlock(&data->philos_ate_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
