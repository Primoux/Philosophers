/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:27:34 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/11 09:02:21 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shared_state.h"
#include "style.h"

__uint32_t	mutex_get_data(t_mutex *mutex)
{
	__uint32_t	data;

	pthread_mutex_lock(&mutex->mutex);
	data = mutex->data;
	pthread_mutex_unlock(&mutex->mutex);
	return (data);
}
void	mutex_set_data(t_mutex *mutex, __uint32_t data)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->data = data;
	pthread_mutex_unlock(&mutex->mutex);
}

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

int	finished_meal(t_philo *philo)
{
	if (mutex_get_data(&philo->sim_data->finished_meal_mutex) >= philo->sim_data->rules.nbr_of_philo)
		return (1);
	return (0);
}

int	safe_printf(t_philo *philo, char *str)
{
	if (mutex_get_data(&philo->sim_data->death_mutex))
		return (1);
	if (check_own_death(philo))
		return (1);
	if (finished_meal(philo))
		return (1);
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
