/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:26:34 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/16 00:39:55 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_rotine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	thinking(philo);

	if(philo->id % 2 == 1)
		ft_wait(philo->data->t_eat / 2);
	
	
	int counter = 0;
	while(1)
	{
		if (philo->data->dead_flag == 1)
		{
			// printf("philo mat");
			// write_status(philo, "is dead !");
			break;
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
		counter++;	
		if(counter > 3)
			break;
		usleep(300);
	}

	return NULL;
}

int    create_threads(t_data *data, t_philo *philo)
{
    int	i;
	
	i = 0;
	while(i < data->nb_philos)
	{
		if(pthread_create(&data->philos[i].thread, NULL, philo_rotine, &data->philos[i]))
			return(print_error(2,"fail to create thread\n"), 1);
		i++;
	}
	while (!data->dead_flag)
		check_dead(philo);
	return (0);
}