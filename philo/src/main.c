/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:47:53 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 00:54:10 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "philo.h"
#include "style.h"

int	main(int argc, char **argv)
{
	t_sim_data	*sim_data;

	sim_data = NULL;
	if (parse_argument(argc, argv, &sim_data))
		return (EXIT_FAILURE);
	print_sim(*sim_data);
	free(sim_data);
	return (EXIT_SUCCESS);
}
