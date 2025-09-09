/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:05:02 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/09 01:28:45 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include <unistd.h>

int	start_simulation(t_sim_data *sim_data)
{
	__uint64_t	i;

	get_time_to_msec(&sim_data->start_mutex.data);
	mutex_unlock(&sim_data->start_mutex);
	i = 0;
	while (i < sim_data->rules.nbr_of_philo)
	{
		pthread_join(sim_data->tab_philo[i].thread.thread, NULL);
		++i;
	}
	return (EXIT_SUCCESS);
}
