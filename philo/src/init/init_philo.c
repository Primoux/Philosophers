/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:04:46 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/25 22:50:09 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "philo.h"
#include "shared_state.h"
#include <unistd.h>

void	get_good_fork(t_sim_data *sim_data, int nbr_philo, int index)
{
	if (index != nbr_philo - 1)
	{
		sim_data->tab_philo[index].left_fork = &sim_data->tab_fork[index];
		sim_data->tab_philo[index].right_fork = &sim_data->tab_fork[index + 1];
	}
	else
	{
		sim_data->tab_philo[index].left_fork = &sim_data->tab_fork[index];
		sim_data->tab_philo[index].right_fork = &sim_data->tab_fork[0];
	}
}

static void	cleanup_philo_threads(t_sim_data *sim_data, int count)
{
	while (count-- > 0)
	{
		pthread_mutex_destroy(&sim_data->tab_philo[count]
			.thread.last_meal.mutex);
		pthread_detach(sim_data->tab_philo[count].thread.thread);
	}
	write(STDERR_FILENO, "Error: failed to create philosopher thread\n", 44);
}

static int	init_single_philo(t_sim_data *sim_data, int i, int nbr_philo)
{
	sim_data->rules.nbr_of_philo_initialized = i;
	if (pthread_mutex_init(&sim_data->tab_philo[i].thread.last_meal.mutex,
			NULL))
		return (1);
	sim_data->tab_philo[i].thread.last_meal.data = 0;
	sim_data->tab_philo[i].thread.nbr_meal = 0;
	sim_data->tab_philo[i].thread.id = i + 1;
	sim_data->tab_philo[i].sim_data = sim_data;
	get_good_fork(sim_data, nbr_philo, i);
	return (0);
}

int	init_philo(t_sim_data *sim_data, int nbr_philo)
{
	int	i;

	i = 0;
	sim_data->tab_philo = malloc(sizeof(t_philo) * nbr_philo + 1);
	if (!sim_data->tab_philo)
		return (EXIT_FAILURE);
	while (i < nbr_philo)
	{
		if (init_single_philo(sim_data, i, nbr_philo))
		{
			free(sim_data->tab_philo);
			return (1);
		}
		if (pthread_create(&sim_data->tab_philo[i].thread.thread,
				NULL, &start_routine, &sim_data->tab_philo[i]))
		{
			pthread_mutex_unlock(&sim_data->start_mutex.mutex);
			if (i > 0)
				cleanup_philo_threads(sim_data, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
