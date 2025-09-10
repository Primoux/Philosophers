/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:50 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/10 11:13:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include "style.h"
#include <unistd.h>

int	sleeping(t_philo *philo)
{
	__uint32_t	now;
	__uint32_t	last_meal;
	__uint32_t	remaining;
	__uint32_t	sleep_time_ms;
	int			time_to_sleep;

	if (safe_printf(philo, "is sleeping"))
		return (1);
	now = get_time_interval_in_msec(&philo->sim_data->start_mutex);
	pthread_mutex_lock(&philo->thread.last_meal.mutex);
	last_meal = philo->thread.last_meal.data;
	pthread_mutex_unlock(&philo->thread.last_meal.mutex);
	if (now >= last_meal + philo->sim_data->rules.time_to_die)
	{
		mutex_set_data(&philo->sim_data->death_mutex, 1);
		return (1);
	}
	remaining = (last_meal + philo->sim_data->rules.time_to_die) - now;
	sleep_time_ms = philo->sim_data->rules.time_to_sleep;
	// usleep(get_time_min(remaining, sleep_time_ms) * 1000);
	time_to_sleep = get_time_min(remaining, sleep_time_ms) * 10;
	for (int i = 0; i < time_to_sleep; i++)
	{
		if (mutex_get_data(&philo->sim_data->death_mutex))
			return (1);
		usleep(1000);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	if (safe_printf(philo, "is thinking"))
		return (1);
	return (0);
}

int	catch_fork(t_philo *philo, t_mutex *fork)
{
	while (1)
	{
		if (mutex_get_data(&philo->sim_data->death_mutex))
			return (1);
		if (mutex_compare_and_swap(fork, TAKEN) == 0)
		{
			if (safe_printf(philo, "has taken a fork"))
			{
				mutex_set_data(fork, FREE);
				return (1);
			}
			break ;
		}
		usleep(100);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	__uint32_t	time;

	if (catch_fork(philo, philo->left_fork))
		return (1);
	if (catch_fork(philo, philo->right_fork))
		return (1);
	mutex_set_data(&philo->thread.nbr_meal,
		mutex_get_data(&philo->thread.nbr_meal) + 1);
	time = get_time_interval_in_msec(&philo->sim_data->start_mutex);
	safe_printf(philo, "is eating");
	mutex_set_data(&philo->thread.last_meal, (__int32_t)time);
	usleep(philo->sim_data->rules.time_to_eat * 1000);
	mutex_set_data(philo->left_fork, FREE);
	mutex_set_data(philo->right_fork, FREE);
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thinking(philo);
	if (philo->thread.id % 2 == 0)
		usleep(philo->sim_data->rules.time_to_eat / 2 * 1000);
	while (1)
	{
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
		if (philo->sim_data->rules.nbr_of_meal != -1)
		{
			if (mutex_get_data(&philo->thread.nbr_meal) >= philo->sim_data->rules.nbr_of_meal)
				break ;
		}
	}
	return (NULL);
}
