/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:11:02 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/17 15:45:35 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(t_philo *philo, char *color, char *action)
{
	long	current_time;

	current_time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("%s %ld  %d  %s\n", color, current_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	write_status(t_philo *philo, char *color, char *action)
{
	if (get_dead_flag(philo) || philo->data->philos_ate)
		return ;
	status(philo, color, action);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	write_status(philo, VIOLET, "has taken a fork");
	write_status(philo, VIOLET, "has taken a fork");
	write_status(philo, GREEN, "is eating");
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
	write_status(philo, WHITE, "is thinking");
}

void	sleeping(t_philo *philo)
{
	write_status(philo, BLUE, "is sleeping");
	ft_wait(philo->data->t_sleep);
}
