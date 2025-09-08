/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:27:34 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 20:07:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shared_state.h"
#include "style.h"

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
}

void	mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->mutex);
}

__uint32_t	mutex_get_data(t_mutex *mutex)
{
	__uint32_t	data;

	data = 0;
	mutex_lock(mutex);
	data = mutex->data;
	mutex_unlock(mutex);
	return (data);
}
void	mutex_set_data(t_mutex *mutex, __uint32_t data)
{
	mutex_lock(mutex);
	mutex->data = data;
	mutex_unlock(mutex);
}

void	safe_printf(t_philo *philo, char *str, int mode)
{
	const char	*color[5] = {RED, GREEN, YELLOW, MAGENTA, CYAN};

	mutex_lock(&philo->sim_data->print_mutex);
	printf("%s[%d]\t%zu%s%s%s\n", BOLD,
		get_time_interval_in_msec(&philo->sim_data->start_mutex),
		philo->thread.id, color[mode], str, RST);
	mutex_unlock(&philo->sim_data->print_mutex);
}
