/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:04:46 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 03:23:56 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "philo.h"
#include "shared_state.h"
#include "utils.h"
#include <unistd.h>

static void	get_good_fork(t_sim_data *sim_data, __uint32_t nbr_philo,
		__uint32_t index)
{
	if (index != nbr_philo - 1U)
	{
		sim_data->tab_philo[index].left_fork = &sim_data->tab_fork[index];
		sim_data->tab_philo[index].right_fork = &sim_data->tab_fork[index + 1U];
	}
	else
	{
		sim_data->tab_philo[index].left_fork = &sim_data->tab_fork[index];
		sim_data->tab_philo[index].right_fork = &sim_data->tab_fork[0];
	}
}

static int	init_single_philo(t_sim_data *sim_data, __uint32_t i,
		__uint32_t nbr_philo)
{
	sim_data->rules.nbr_of_philo_initialized = (__int32_t)i;
	if (pthread_mutex_init(&sim_data->tab_philo[i].thread.last_meal.mutex,
			NULL))
		return (1);
	sim_data->tab_philo[i].thread.last_meal.data = 0U;
	sim_data->tab_philo[i].thread.nbr_meal = 0;
	sim_data->tab_philo[i].thread.id = i + 1U;
	sim_data->tab_philo[i].sim_data = sim_data;
	get_good_fork(sim_data, nbr_philo, i);
	return (0);
}

int	init_philo(t_sim_data *sim_data, __uint32_t nbr_philo)
{
	__uint32_t	i;

	i = 0;
	sim_data->tab_philo = malloc(sizeof(t_philo) * nbr_philo + 1U);
	if (!sim_data->tab_philo)
	{
		write(STDERR_FILENO, "Error: malloc failed\n", 22);
		return (EXIT_FAILURE);
	}
	while (i < nbr_philo)
	{
		if (init_single_philo(sim_data, i, nbr_philo))
		{
			free(sim_data->tab_philo);
			return (EXIT_FAILURE);
		}
		if (pthread_create(&sim_data->tab_philo[i].thread.thread, NULL,
				&start_routine, &sim_data->tab_philo[i]))
		{
			pthread_mutex_unlock(&sim_data->start_mutex.mutex);
			if (i > 0)
				cleanup_philo_threads(sim_data, (__int32_t)i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
