/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:07:46 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/11 11:17:31 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_tab_return_null(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

void	clean_one_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(&mutex->mutex);
}

void	clean_all_mutex(t_sim_data *sim_data)
{
	int	i;

	pthread_mutex_destroy(&sim_data->death_mutex.mutex);
	pthread_mutex_destroy(&sim_data->finished_meal_mutex.mutex);
	pthread_mutex_destroy(&sim_data->print_mutex.mutex);
	pthread_mutex_destroy(&sim_data->start_mutex.mutex);
	i = 0;
	while (i < sim_data->rules.nbr_of_philo_initialized)
	{
		if (&sim_data->tab_philo[i])
		{
			clean_one_mutex(&sim_data->tab_philo[i].thread.last_meal);
		}
		++i;
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
