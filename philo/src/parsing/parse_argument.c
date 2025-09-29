/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:53:55 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 03:33:29 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include "utils.h"
#include <unistd.h>

static int	check_nbr_arg(int ac)
{
	if (ac != 5 && ac != 6)
	{
		write(STDERR_FILENO, "Error: Invalid nbr of arguments\n", 33);
		write(STDERR_FILENO, "./philo <nbr_of_philo> <TTD> ", 30);
		write(STDERR_FILENO, "<TTE <TTS> [nbr_of_meals]\n", 27);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_argument(int ac, char **av, t_rules *rules)
{
	if (check_nbr_arg(ac) || init_sim_data(av, rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
