/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:21:40 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 20:36:53 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "philo.h"
#include "utils.h"

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
		sim_data->tab_philo[i].id = i;
		sim_data->tab_philo[i].sim_data = sim_data;
		get_good_fork(sim_data, nbr_philo, i);
		if (pthread_create(&sim_data->tab_philo[i].thread, NULL, &start_routine,
				&sim_data->tab_philo[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_fork(t_sim_data *sim_data, int nbr_philo)
{
	int	i;

	i = 0;
	sim_data->tab_fork = malloc(sizeof(t_fork) * nbr_philo + 1);
	if (!sim_data->tab_fork)
		return (EXIT_FAILURE);
	while (i < nbr_philo)
	{
		sim_data->tab_fork[i].id = i;
		sim_data->tab_fork[i].is_taken = FALSE;
		pthread_mutex_init(&sim_data->tab_fork[i].is_taken_mutex, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_simulation(t_sim_data *sim_data)
{
	pthread_mutex_init(&sim_data->start_mutex, NULL);
	pthread_mutex_init(&sim_data->print_mutex, NULL);
	sim_data->start_flag = FALSE;
	if (init_fork(sim_data, sim_data->nbr_of_philo))
		return (EXIT_FAILURE);
	if (init_philo(sim_data, sim_data->nbr_of_philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
