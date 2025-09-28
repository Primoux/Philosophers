/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:07:46 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/28 22:19:59 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <unistd.h>

void	cleanup_philo_threads(t_sim_data *sim_data, int count)
{
	while (count-- > 0)
	{
		pthread_mutex_destroy(&sim_data->tab_philo[count].thread.last_meal.mutex);
		pthread_detach(sim_data->tab_philo[count].thread.thread);
	}
	write(STDERR_FILENO, "Error: failed to create a philosopher\n", 39);
}

static void	clean_all_mutex(t_sim_data *sim_data)
{
	__uint32_t	i;

	pthread_mutex_destroy(&sim_data->death_mutex.mutex);
	pthread_mutex_destroy(&sim_data->finished_meal_mutex.mutex);
	pthread_mutex_destroy(&sim_data->print_mutex.mutex);
	pthread_mutex_destroy(&sim_data->start_mutex.mutex);
	if (sim_data->tab_fork)
	{
		i = 0;
		while (i < sim_data->rules.nbr_of_philo)
		{
			pthread_mutex_destroy(&sim_data->tab_fork[i].mutex);
			++i;
		}
	}
}

void	cleanup_resources(t_sim_data *sim_data)
{
	if (sim_data)
	{
		clean_all_mutex(sim_data);
		if (sim_data->tab_philo)
			free(sim_data->tab_philo);
		if (sim_data->tab_fork)
			free(sim_data->tab_fork);
		free(sim_data);
	}
}
