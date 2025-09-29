/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:13:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 03:16:48 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include "utils.h"
#include <unistd.h>

static void	put_in_tab(int i, __uint32_t nbr, t_rules *rules)
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
		rules->nbr_of_meal = (__int32_t)nbr;
}

static int	check_arg(char *arg, t_rules *rules, int i)
{
	int	error;
	int	nbr;

	nbr = ft_atoi(arg, &error);
	if (error != 0)
	{
		write(STDERR_FILENO, "Error: numeric overflow\n", 25);
		return (EXIT_FAILURE);
	}
	else if (nbr <= 0)
	{
		write(STDERR_FILENO, "Error: invalid argument\n", 25);
		return (EXIT_FAILURE);
	}
	put_in_tab(i, (__uint32_t)nbr, rules);
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
