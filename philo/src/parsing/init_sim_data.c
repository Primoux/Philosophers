/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:13:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 00:35:59 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include "utils.h"

int	put_in_struct(char *arg, t_sim_data *sim_data, int i)
{
	int	error;
	int	nbr;

	error = 0;
	nbr = ft_atoi(arg, &error);
	if (error != 0)
		return (EXIT_FAILURE);
	if (i == 1)
		sim_data->nbr_of_philo = nbr;
	else if (i == 2)
		sim_data->time_to_die = nbr;
	else if (i == 3)
		sim_data->time_to_eat = nbr;
	else if (i == 4)
		sim_data->time_to_sleep = nbr;
	else if (i == 5)
		sim_data->nbr_of_meal = nbr;
	return (EXIT_SUCCESS);
}

int	fill_simulation_data(char **av, t_sim_data *sim_data)
{
	int	i;

	i = 1;
	sim_data->nbr_of_meal = -1;
	while (av[i])
	{
		if (is_all_digits(av[i]) || put_in_struct(av[i], sim_data, i))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	init_sim_data(char **av, t_sim_data **sim_data)
{
	*sim_data = malloc(sizeof(t_sim_data));
	if (!*sim_data)
		return (EXIT_FAILURE);
	if (fill_simulation_data(av, *sim_data))
	{
		free(*sim_data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
