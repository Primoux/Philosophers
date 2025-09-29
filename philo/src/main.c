/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:47:53 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/29 17:16:12 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "style.h"
#include "utils.h"
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_sim_data	*sim_data;

	sim_data = malloc(sizeof(t_sim_data));
	if (!sim_data)
	{
		write(STDERR_FILENO, "Error: malloc failed in main\n", 30);
		return (EXIT_FAILURE);
	}
	memset(sim_data, 0, sizeof(t_sim_data));
	if (parse_argument(argc, argv, &sim_data->rules))
		return (EXIT_FAILURE);
	if (init_simulation(sim_data) || start_simulation(sim_data))
	{
		cleanup_resources(sim_data);
		return (EXIT_FAILURE);
	}
	cleanup_resources(sim_data);
	return (EXIT_SUCCESS);
}
