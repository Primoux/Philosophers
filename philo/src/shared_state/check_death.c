/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:42:57 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/25 17:45:34 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shared_state.h"

int	check_own_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_data->death_mutex.mutex);
	if (get_time_interval_in_msec(&philo->sim_data->start_mutex)
		- mutex_get_data(&philo->thread.last_meal) >= philo->sim_data->rules.time_to_die)
	{
		philo->sim_data->death_mutex.data = 1;
		pthread_mutex_unlock(&philo->sim_data->death_mutex.mutex);
		pthread_mutex_lock(&philo->sim_data->print_mutex.mutex);
		printf("%d %zu died\n",
			get_time_interval_in_msec(&philo->sim_data->start_mutex),
			philo->thread.id);
		pthread_mutex_unlock(&philo->sim_data->print_mutex.mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim_data->death_mutex.mutex);
	return (0);
}
