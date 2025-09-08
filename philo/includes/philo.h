/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:48:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 16:27:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_sim_data	t_sim_data;

typedef enum e_bool
{
	FALSE,
	TRUE
}							t_bool;

typedef struct s_mutex
{
	int						id;
	pthread_mutex_t			is_taken_mutex;
	t_bool					is_taken;
}							t_mutex;

typedef struct s_philo
{
	t_sim_data				*sim_data;
	t_mutex					*left_fork;
	t_mutex					*right_fork;
	pthread_t				thread;
	int						id;
}							t_philo;

typedef struct s_rules
{
	int						nbr_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nbr_of_meal;
}							t_rules;

typedef struct s_sim_data
{
	pthread_mutex_t			start_mutex;
	pthread_mutex_t			print_mutex;
	t_rules					rules;
	t_philo					*tab_philo;
	t_mutex					*tab_fork;
}							t_sim_data;

int							parse_argument(int ac, char **av,
								t_rules *rules);
int							init_sim_data(char **av, t_rules *rules);
int							init_simulation(t_sim_data *sim_data);

#endif
