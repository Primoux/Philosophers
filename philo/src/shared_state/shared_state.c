/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:27:34 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 18:15:37 by enchevri         ###   ########lyon.fr   */
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

void	safe_printf(t_mutex *mutex, char *str, int mode)
{
	const char	*color[5] = {RED, GREEN, YELLOW, MAGENTA, CYAN};

	mutex_lock(mutex);
	printf("%s%s%s%s\n", BOLD, color[mode], str, RST);
	mutex_unlock(mutex);
}
