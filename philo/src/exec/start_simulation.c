/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:05:02 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 16:00:49 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	start_simulation(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&sim_data->start_mutex);
	while (i < sim_data->rules.nbr_of_philo)
	{
		pthread_join(sim_data->tab_philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
