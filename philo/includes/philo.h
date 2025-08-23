/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:48:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 00:11:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;

}					t_fork;

typedef struct s_philo
{
	size_t			id;
	t_fork			*left_fork;
	t_fork			*right_fork;
}					t_philo;

typedef struct s_sim_data
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meal;
	t_philo			*tab_philo;
	t_fork			*tab_fork;
}					t_sim_data;

int					parse_argument(int ac, char **av, t_sim_data **sim_data);
int					init_sim_data(char **av, t_sim_data **sim_data);
#endif
