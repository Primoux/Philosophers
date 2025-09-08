/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:59:52 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 19:51:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "shared_state.h"
#include <sys/time.h>

void	get_time_to_msec(__uint32_t *time)
{
	struct timeval	tv;
	__uint32_t		sec;
	__uint32_t		usec;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec * 1000;
	usec = tv.tv_usec / 1000;
	*time = sec + usec;
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
