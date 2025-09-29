/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:21:40 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 03:19:25 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "philo.h"
#include "shared_state.h"
#include "utils.h"
#include <style.h>
#include <unistd.h>

static int	init_and_put_fork(t_sim_data *sim_data, __uint32_t nbr_philo)
{
	__uint32_t	i;

	i = 0;
	sim_data->tab_fork = malloc(sizeof(t_mutex) * (nbr_philo + 1U));
	if (!sim_data->tab_fork)
	{
		write(STDERR_FILENO, "Error : malloc failed", 22);
		return (EXIT_FAILURE);
	}
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&sim_data->tab_fork[i].mutex, NULL))
		{
			if (i > 0)
			{
				while (i-- > 0)
					pthread_mutex_destroy(&sim_data->tab_fork[i].mutex);
			}
			return (EXIT_FAILURE);
		}
		sim_data->tab_fork[i].id = i + 1U;
		sim_data->tab_fork[i].data = 0U;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_start_print_mutex(t_sim_data *sim_data)
{
	if (pthread_mutex_init(&sim_data->start_mutex.mutex, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&sim_data->print_mutex.mutex, NULL))
	{
		pthread_mutex_destroy(&sim_data->start_mutex.mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_death_finished_mutex(t_sim_data *sim_data)
{
	if (pthread_mutex_init(&sim_data->death_mutex.mutex, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&sim_data->finished_meal_mutex.mutex, NULL))
	{
		pthread_mutex_destroy(&sim_data->death_mutex.mutex);
		return (EXIT_FAILURE);
	}
	sim_data->finished_meal_mutex.data = 0;
	return (EXIT_SUCCESS);
}

static int	create_sim_mutex(t_sim_data *sim_data)
{
	if (init_start_print_mutex(sim_data))
		return (EXIT_FAILURE);
	if (init_death_finished_mutex(sim_data))
	{
		pthread_mutex_destroy(&sim_data->start_mutex.mutex);
		pthread_mutex_destroy(&sim_data->print_mutex.mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_simulation(t_sim_data *sim_data)
{
	if (create_sim_mutex(sim_data))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&sim_data->start_mutex.mutex);
	if (init_and_put_fork(sim_data, sim_data->rules.nbr_of_philo))
		return (EXIT_FAILURE);
	if (init_philo(sim_data, sim_data->rules.nbr_of_philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
