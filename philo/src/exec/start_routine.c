/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:50 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 20:14:08 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include "style.h"
#include <unistd.h>

void thinking(t_philo *philo)
{
	safe_printf(philo, "\tis thinking", 2);
}
void eating(t_philo *philo)
{
	safe_printf(philo, "\tis eating", 1);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	mutex_get_data(&philo->sim_data->start_mutex);
	while (get_time_interval_in_msec(&philo->sim_data->start_mutex) <= 1000)
	{
		thinking(philo);
		eating(philo);
		usleep(1000);
	}
	return (NULL);
}
