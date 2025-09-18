/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:50 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/17 17:31:03 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "exec.h"
#include "shared_state.h"
#include "style.h"
#include <unistd.h>



void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->sim_data->start_mutex.mutex);
	pthread_mutex_unlock(&philo->sim_data->start_mutex.mutex);
	if (thinking(philo))
		return (NULL);
	if (philo->thread.id % 2 == 0)
		if (ft_usleep(philo, philo->sim_data->rules.time_to_eat
				/ 2 * 1000, get_time_to_msec()))
			return (NULL);
	while (1)
	{
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}
