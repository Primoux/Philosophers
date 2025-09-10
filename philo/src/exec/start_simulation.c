/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:05:02 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/10 04:51:22 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include <unistd.h>

int	start_simulation(t_sim_data *sim_data)
{
	__uint64_t	i;

	get_time_to_msec(&sim_data->start_mutex.data);
	pthread_mutex_unlock(&sim_data->start_mutex.mutex);
	i = 0;
	while (i < sim_data->rules.nbr_of_philo)
	{
		pthread_join(sim_data->tab_philo[i].thread.thread, NULL);
		++i;
	}
	return (EXIT_SUCCESS);
}
