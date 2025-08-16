/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:26:34 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/16 22:08:51 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thinking(philo);
	if (philo->id % 2 == 1)
		ft_wait(philo->data->t_eat / 2);
	while (1)
	{
		if (get_dead_flag(philo))
			break ;
		if (philo->data->philos_ate == 1)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thinking(philo);
	pthread_mutex_lock(philo->left_fork);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->t_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_wait(philo->data->t_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	create_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	if (!data || !philo)
		return (print_error(2, "Invalid data or philosophers\n"), 1);
	if (philo->data->nb_philos == 1)
	{
		pthread_create(&data->philos[0].thread, NULL, one_philo,
			&data->philos[0]);
		printf("one philo\n");
	}
	else
	{
		while (i < data->nb_philos)
		{
			if (pthread_create(&data->philos[i].thread, NULL, philo_rotine,
					&data->philos[i]))
				return (print_error(2, "fail to create thread\n"), 1);
			i++;
		}
	}
	while (!get_dead_flag(philo) && !data->philos_ate)
		check_dead(philo);

	return (0);
}