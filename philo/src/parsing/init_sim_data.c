/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:13:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/25 20:16:52 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include "utils.h"
#include <unistd.h>

static void	put_in_tab(int i, int nbr, t_rules *rules)
{
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
}

static int	check_arg(char *arg, t_rules *rules, int i)
{
	int	error;
	int	nbr;

	nbr = ft_atoi(arg, &error);
	if (error != 0)
	{
		if (write(STDERR_FILENO, "Error: numeric overflow\n", 25) == -1)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	else if (nbr <= 0)
	{
		if (write(STDERR_FILENO, "Error: invalid argument\n", 25) == -1)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	put_in_tab(i, nbr, rules);
	return (EXIT_SUCCESS);
}

static int	fill_simulation_data(char **av, t_rules *rules)
{
	int	i;

	i = 1;
	rules->nbr_of_meal = -1;
	while (av[i])
	{
		if (is_all_digits(av[i]))
			return (EXIT_FAILURE);
		if (check_arg(av[i], rules, i))
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
