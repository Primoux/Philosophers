/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:50 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/09 03:03:58 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include "style.h"
#include <unistd.h>

int check_death(t_philo *philo)
{
	if (mutex_get_data(&philo->sim_data->death_mutex))
		return (1);
	if (get_time_interval_in_msec(&philo->sim_data->start_mutex)
		- mutex_get_data(&philo->thread.last_meal) > philo->sim_data->rules.time_to_die)
	{
		safe_printf(philo, "died", 5);
		return (1);
	}
	return (0);
}

int sleeping(t_philo *philo)
{		
	if (check_death(philo))
		return (1);
	safe_printf(philo, "is sleeping", 5);
	usleep(philo->sim_data->rules.time_to_sleep * 1000);
	return (0);
}

int thinking(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	safe_printf(philo, "is thinking", 5);
	return (0);
}

int catch_fork(t_philo *philo,t_mutex *fork)
{
	while (1)
	{
		if (check_death(philo))
			return (1);
		if (mutex_get_data(fork) == 0)
		{
			mutex_lock(fork);
			fork->data = 1;
			safe_printf(philo, "has taken a fork", 5);
			break ;
		}
	}
	return (0);
}

int eating(t_philo *philo)
{
	if (catch_fork(philo, philo->left_fork))
		return (1);
	if (catch_fork(philo, philo->right_fork))
		return (1);
	if (check_death(philo))
	{
		mutex_unlock(philo->left_fork);
		mutex_set_data(philo->left_fork, 0);
		mutex_unlock(philo->right_fork);
		mutex_set_data(philo->right_fork, 0);
		return (1);
	}
	safe_printf(philo, "is eating", 5);
	mutex_set_data(&philo->thread.nbr_meal, mutex_get_data(&philo->thread.nbr_meal) + 1);
	mutex_set_data(&philo->thread.last_meal, get_time_interval_in_msec(&philo->sim_data->start_mutex));
	usleep(philo->sim_data->rules.time_to_eat * 1000);
	mutex_unlock(philo->left_fork);
	mutex_set_data(philo->left_fork, 0);
	mutex_unlock(philo->right_fork);
	mutex_set_data(philo->right_fork, 0);
	return (0);
}



void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	mutex_get_data(&philo->sim_data->start_mutex);
	while (1)
	{
		if (thinking(philo))
			return (NULL);
		if (eating(philo))
			return (NULL);
		if (philo->sim_data->rules.nbr_of_meal != -1)
		{
			if (mutex_get_data(&philo->thread.nbr_meal) >= philo->sim_data->rules.nbr_of_meal)
				break ;
		}
		if (sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
