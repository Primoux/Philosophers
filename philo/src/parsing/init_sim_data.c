/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:13:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/04 03:23:11 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include "utils.h"
#include <unistd.h>

int	put_in_struct(char *arg, t_rules *rules, int i)
{
	int	error;
	int	nbr;

	nbr = ft_atoi(arg, &error);
	if (error != 0)
	{
		write(STDERR_FILENO, "Error: numeric overflow at \n", 25);
		return (EXIT_FAILURE);
	}
	else if (nbr <= 0)
	{
		write(STDERR_FILENO, "Error: invalid argument\n", 25);
		return (EXIT_FAILURE);
	}
	if (i == 1)
		rules->nbr_of_philo = nbr;
	else if (i == 2)
		rules->time_to_die = nbr;
	else if (i == 3)
		rules->time_to_eat = nbr;
	else if (i == 4)
		rules->time_to_sleep = nbr;
	else if (i == 5)
		rules->nbr_of_meal = nbr;
	return (EXIT_SUCCESS);
}

int	fill_simulation_data(char **av, t_rules *rules)
{
	int	i;

	i = 1;
	rules->nbr_of_meal = -1;
	while (av[i])
	{
		if (is_all_digits(av[i]))
			return (EXIT_FAILURE);
		if (put_in_struct(av[i], rules, i))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	init_sim_data(char **av, t_rules *rules)
{
	if (fill_simulation_data(av, rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
