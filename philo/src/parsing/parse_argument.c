/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:53:55 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 17:06:13 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include "utils.h"
#include <unistd.h>

int	check_nbr_arg(int ac)
{
	if (ac != 5 && ac != 6)
	{
		write(STDERR_FILENO, "Error: Invalid number of arguments\n", 36);
		write(STDERR_FILENO, "./philo <number_of_philosophers> <time_to_die> ",
			48);
		write(STDERR_FILENO, "<time_to_eat <time_to_sleep> [number_of_meals]\n",
			48);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_argument(int ac, char **av, t_sim_data **sim_data)
{
	if (check_nbr_arg(ac) || init_sim_data(av, sim_data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
