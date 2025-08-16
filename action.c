/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:11:02 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/16 22:38:08 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(t_philo *philo, char *action)
{
	long	current_time;

	current_time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("%ld  %d  %s \n", current_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	write_status(t_philo *philo, char *action)
{
	if (get_dead_flag(philo) || philo->data->philos_ate)
		return ;
	status(philo, action);
}

void	ft_wait(int ms)
{
	int	start;

	start = get_current_time();
	while (get_current_time() - start < ms)
		usleep(200);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	write_status(philo, "has taken a fork");
	write_status(philo, "has taken a fork");
	write_status(philo, "is eating");

	pthread_mutex_lock(&philo->meal_mutex);
	philo->t_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);

	ft_wait(philo->data->t_eat);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->data->count_mutex);
	philo->count_meals++;
	pthread_mutex_unlock(&philo->data->count_mutex);
}

void	thinking(t_philo *philo)
{
	write_status(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	write_status(philo, "is sleeping");
	ft_wait(philo->data->t_sleep);
}
