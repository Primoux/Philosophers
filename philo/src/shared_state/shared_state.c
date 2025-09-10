/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:27:34 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/10 10:24:55 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shared_state.h"
#include "style.h"

__int32_t	mutex_get_data(t_mutex *mutex)
{
	__int32_t	data;

	data = 0;
	pthread_mutex_lock(&mutex->mutex);
	data = mutex->data;
	pthread_mutex_unlock(&mutex->mutex);
	return (data);
}
void	mutex_set_data(t_mutex *mutex, __int32_t data)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->data = data;
	pthread_mutex_unlock(&mutex->mutex);
}

int	safe_printf(t_philo *philo, char *str)
{
	if (mutex_get_data(&philo->sim_data->death_mutex))
		return (1);
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
	pthread_mutex_lock(&philo->sim_data->print_mutex.mutex);
	printf("%d %zu %s\n",
		get_time_interval_in_msec(&philo->sim_data->start_mutex),
		philo->thread.id, str);
	pthread_mutex_unlock(&philo->sim_data->print_mutex.mutex);
	return (0);
}

int	mutex_compare_and_swap(t_mutex *mutex, __uint32_t state)
{
	pthread_mutex_lock(&mutex->mutex);
	if (mutex->data == state)
	{
		pthread_mutex_unlock(&mutex->mutex);
		return (1);
	}
	else
	{
		mutex->data = state;
		pthread_mutex_unlock(&mutex->mutex);
		return (0);
	}
}
