/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:08:51 by nikhtib           #+#    #+#             */
/*   Updated: 2025/08/16 22:08:11 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data				*data;
	int					id;
	pthread_t			thread;
	int					t_last_meal;
	int					count_meals;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		meal_mutex;
}						t_philo;

typedef struct s_data
{
	size_t				start_time;
	int					nb_philos;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					nb_must_eat;
	int					dead_flag;
	int					philos_ate;
	pthread_mutex_t		*forks;
	pthread_mutex_t		max_meal;
	pthread_mutex_t		count_mutex;
	pthread_mutex_t		philos_ate_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	t_philo				*philos;
}						t_data;

pthread_mutex_t			*init_forks(int c);
int						is_number(char c);
int						valid_argument(char **arg);
int						init_data(t_data *data, char **av);
int						create_threads(t_data *data, t_philo *philo);
void					*philo_rotine(void *arg);
int						ft_strlen(char *s);
int						get_current_time(void);
void					print_error(int fd, char *str);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					eating(t_philo *philo);
void					ft_wait(int ms);
void					check_dead(t_philo *philo);
void					write_status(t_philo *philo, char *action);
int						get_dead_flag(t_philo *philo);
int						small_atoi(char *s);
int						check_nb_meals(t_philo *philo);
void					status(t_philo *philo, char *action);
void					assign_forks(t_data *data);
void					wait_treads(t_data *data);
void					destroy_mutex(t_data *data);
#endif