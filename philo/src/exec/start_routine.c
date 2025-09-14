/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:50 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/14 15:21:50 by enzo             ###   ########.fr       */
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
	if (ft_usleep(philo, get_min(remaining, sleep_time_ms) * 1000))
		return (1);
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
		if (mutex_get_data(&philo->sim_data->death_mutex)
			|| check_own_death(philo) || finished_meal(philo))
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

void	update_finished_meal(t_philo *philo)
{
	if (philo->sim_data->rules.nbr_of_meal != -1)
	{
		if (philo->thread.nbr_meal == philo->sim_data->rules.nbr_of_meal)
		{
			mutex_set_data(&philo->sim_data->finished_meal_mutex,
				mutex_get_data(&philo->sim_data->finished_meal_mutex) + 1);
		}
	}
}

int	eating(t_philo *philo)
{
	__uint32_t	time;

	if (catch_fork(philo, philo->left_fork))
		return (1);
	if (catch_fork(philo, philo->right_fork))
		return (1);
	philo->thread.nbr_meal += 1;
	time = get_time_interval_in_msec(&philo->sim_data->start_mutex);
	if (safe_printf(philo, "is eating"))
		return (1);
	update_finished_meal(philo);
	mutex_set_data(&philo->thread.last_meal, time);
	if (ft_usleep(philo, philo->sim_data->rules.time_to_eat * 1000))
	{
		mutex_set_data(philo->left_fork, FREE);
		mutex_set_data(philo->right_fork, FREE);
		return (1);
	}
	mutex_set_data(philo->left_fork, FREE);
	mutex_set_data(philo->right_fork, FREE);
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (thinking(philo))
		return (NULL);
	if (philo->thread.id % 2 == 0)
		if (ft_usleep(philo, philo->sim_data->rules.time_to_eat / 2 * 1000))
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
