/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:48:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 03:37:40 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_sim_data	t_sim_data;

enum						e_state
{
	FREE,
	TAKEN,
};

typedef struct s_mutex
{
	__uint32_t				id;
	pthread_mutex_t			mutex;
	__uint32_t				data;
}							t_mutex;

typedef struct s_thread
{
	size_t					id;
	__int32_t				nbr_meal;
	t_mutex					last_meal;
	pthread_t				thread;
}							t_thread;

typedef struct s_philo
{
	t_sim_data				*sim_data;
	t_mutex					*left_fork;
	t_mutex					*right_fork;
	t_thread				thread;
}							t_philo;

typedef struct s_rules
{
	__uint32_t				nbr_of_philo;
	__uint32_t				time_to_die;
	__uint32_t				time_to_eat;
	__uint32_t				time_to_sleep;
	__int32_t				nbr_of_meal;
	__int32_t				nbr_of_philo_initialized;
}							t_rules;

typedef struct s_sim_data
{
	t_mutex					start_mutex;
	t_mutex					print_mutex;
	t_rules					rules;
	t_philo					*tab_philo;
	t_mutex					*tab_fork;
	t_mutex					death_mutex;
	t_mutex					finished_meal_mutex;
}							t_sim_data;

int							parse_argument(int ac, char **av, t_rules *rules);
int							init_sim_data(char **av, t_rules *rules);
int							init_simulation(t_sim_data *sim_data);
int							init_philo(t_sim_data *sim_data,
								__uint32_t nbr_philo);
__uint32_t					get_time_to_msec(void);
__uint32_t					get_time_interval_in_msec(t_mutex *mutex);
__int32_t					get_min(__int32_t time1, __int32_t time2);
__uint32_t					ft_usleep(t_philo *philo, __uint32_t time,
								__uint32_t start_time);

#endif
