/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:59:52 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/16 10:23:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include <sys/time.h>
#include <unistd.h>

__uint32_t	get_time_to_msec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

__uint32_t	get_time_interval_in_msec(t_mutex *mutex)
{
	struct timeval	tv;
	__uint32_t		start_time;
	__uint32_t		actual_time;
	__uint32_t		sec;
	__uint32_t		usec;

	start_time = mutex_get_data(mutex);
	gettimeofday(&tv, NULL);
	sec = tv.tv_sec * 1000;
	usec = tv.tv_usec / 1000;
	actual_time = sec + usec;
	return (actual_time - start_time);
}

__int32_t	get_min(__int32_t time1, __int32_t time2)
{
	if (time1 >= time2)
		return (time2);
	else
		return (time1);
}

__uint32_t	ft_usleep(t_philo *philo, __uint32_t time, __uint32_t start_time)
{
	while (get_time_to_msec() - start_time < time / 1000)
	{
		if (mutex_get_data(&philo->sim_data->death_mutex))
			return (1);
		pthread_mutex_lock(&philo->sim_data->death_mutex.mutex);
		if (get_time_interval_in_msec(&philo->sim_data->start_mutex)
			- mutex_get_data(&philo->thread.last_meal) >= philo->sim_data->rules
			.time_to_die)
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
		if (finished_meal(philo))
			return (1);
		usleep(450);
	}
	return (0);
}
