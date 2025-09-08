/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:48:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 17:07:03 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_sim_data	t_sim_data;

typedef struct s_mutex
{
	int						id;
	pthread_mutex_t			mutex;
	__uint32_t				data;
}							t_mutex;

typedef struct s_thread
{
	int						id;
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
	__int32_t				nbr_of_philo;
	__int32_t				time_to_die;
	__int32_t				time_to_eat;
	__int32_t				time_to_sleep;
	__int32_t				nbr_of_meal;
}							t_rules;

typedef struct s_sim_data
{
	t_mutex					start_mutex;
	t_mutex					print_mutex;
	t_rules					rules;
	t_philo					*tab_philo;
	t_mutex					*tab_fork;
}							t_sim_data;

int							parse_argument(int ac, char **av, t_rules *rules);
int							init_sim_data(char **av, t_rules *rules);
int							init_simulation(t_sim_data *sim_data);

#endif
