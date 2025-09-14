/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:21:40 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/13 03:08:45 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "philo.h"
#include "shared_state.h"
#include "utils.h"
#include <style.h>

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

int	init_philo(t_sim_data *sim_data, int nbr_philo)
{
	int	i;

	i = 0;
	sim_data->tab_philo = malloc(sizeof(t_philo) * nbr_philo + 1);
	if (!sim_data->tab_philo)
		return (EXIT_FAILURE);
	while (i < nbr_philo)
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
		if (pthread_create(&sim_data->tab_philo[i].thread.thread, NULL,
				&start_routine, &sim_data->tab_philo[i]))
			if (i > 0)
			{
				while (i-- > 0)
				{
					pthread_mutex_destroy(&sim_data->tab_philo[i]
						.thread.last_meal.mutex);
					pthread_detach(sim_data->tab_philo[i].thread.thread);
				}
			}
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_and_put_fork(t_sim_data *sim_data, int nbr_philo)
{
	int	i;

	i = 0;
	sim_data->tab_fork = malloc(sizeof(t_mutex) * (nbr_philo + 1));
	if (!sim_data->tab_fork)
		return (EXIT_FAILURE);
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
		sim_data->tab_fork[i].id = i + 1;
		sim_data->tab_fork[i].data = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_sim_mutex(t_sim_data *sim_data)
{
	if (pthread_mutex_init(&sim_data->start_mutex.mutex, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&sim_data->print_mutex.mutex, NULL))
	{
		pthread_mutex_destroy(&sim_data->start_mutex.mutex);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&sim_data->death_mutex.mutex, NULL))
	{
		pthread_mutex_destroy(&sim_data->start_mutex.mutex);
		pthread_mutex_destroy(&sim_data->print_mutex.mutex);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&sim_data->finished_meal_mutex.mutex, NULL))
	{
		pthread_mutex_destroy(&sim_data->start_mutex.mutex);
		pthread_mutex_destroy(&sim_data->print_mutex.mutex);
		pthread_mutex_destroy(&sim_data->death_mutex.mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_simulation(t_sim_data *sim_data)
{
	if (create_sim_mutex(sim_data))
		return (EXIT_FAILURE);
	sim_data->finished_meal_mutex.data = 0;
	pthread_mutex_lock(&sim_data->start_mutex.mutex);
	if (init_and_put_fork(sim_data, sim_data->rules.nbr_of_philo))
		return (EXIT_FAILURE);
	if (init_philo(sim_data, sim_data->rules.nbr_of_philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
