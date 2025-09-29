/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:22:30 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 03:30:40 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "philo.h"
#include "style.h"

void	print_sim(t_sim_data sim_data)
{
	char	*color;
	char	*format;

	color = GREEN;
	format = BOLD;
	printf("%s%sNbr_of_philo = '%d'%s\n", format, color,
		sim_data.rules.nbr_of_philo, RST);
	printf("%s%sTime_to_die = '%d'%s\n", format, color,
		sim_data.rules.time_to_die, RST);
	printf("%s%sTime_to_eat = '%d'%s\n", format, color,
		sim_data.rules.time_to_eat, RST);
	printf("%s%sTime_to_sleep = '%d'%s\n", format, color,
		sim_data.rules.time_to_sleep, RST);
	if (sim_data.rules.nbr_of_meal == -1)
		color = RED;
	printf("%s%sNbr_of_meal = '%d'%s\n", format, color,
		sim_data.rules.nbr_of_meal, RST);
}
