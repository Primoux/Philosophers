/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:47:53 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 02:14:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "style.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_sim_data	*sim_data;

	sim_data = NULL;
	if (parse_argument(argc, argv, &sim_data))
		return (EXIT_FAILURE);
	print_sim(*sim_data);
	// if (init_simulation(sim_data))
	// {
	// 	cleanup_simulation(sim_data);
	// 	return (EXIT_FAILURE);
	// }
	// if (start_simulation(sim_data))
	// {
	// 	cleanup_simulation(sim_data);
	// 	return (EXIT_FAILURE);
	// }
	cleanup_resources(sim_data);
	return (EXIT_SUCCESS);
}
