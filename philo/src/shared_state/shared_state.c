/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:27:34 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/09 02:25:12 by enzo             ###   ########.fr       */
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

__int32_t	mutex_get_data(t_mutex *mutex)
{
	__int32_t	data;

	data = 0;
	mutex_lock(mutex);
	data = mutex->data;
	mutex_unlock(mutex);
	return (data);
}
void	mutex_set_data(t_mutex *mutex, __int32_t data)
{
	mutex_lock(mutex);
	mutex->data = data;
	mutex_unlock(mutex);
}

void	safe_printf(t_philo *philo, char *str, int mode)
{
	const char	*color[6] = {BOLD RED, BOLD GREEN, BOLD YELLOW, BOLD MAGENTA, BOLD CYAN, ""};
	const char	*rst[6] = {RST, RST, RST, RST, RST, ""};

	mutex_lock(&philo->sim_data->print_mutex);
	printf("%d %zu %s%s%s\n",
		get_time_interval_in_msec(&philo->sim_data->start_mutex),
		philo->thread.id, color[mode], str, rst[mode]);
	mutex_unlock(&philo->sim_data->print_mutex);
}
