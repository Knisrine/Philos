/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:43:12 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/15 17:55:09 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_dead_flag(t_philo *philo)
{
    int flag;
    
    pthread_mutex_lock(&philo->data->death_mutex);
    flag = philo->data->dead_flag;
    pthread_mutex_unlock(&philo->data->death_mutex);
    return flag;
}

void     check_dead(t_philo *philo)
{
    int i;
    int time;
    
    i = 0;
    while (!get_dead_flag(philo) && i < philo->data->nb_philos)
    {
        pthread_mutex_lock(philo->meal_mutex);
        time = get_current_time() - philo->data->philos[i].t_last_meal;
        pthread_mutex_unlock(philo->meal_mutex);
        
        if (time >= philo->data->t_die)
        {
            pthread_mutex_lock(&philo->data->death_mutex);
            philo->data->dead_flag = 1;
            pthread_mutex_unlock(&philo->data->death_mutex);
            printf("philo is dead\n");
        }   
            // return;
        i++;
    }
}
