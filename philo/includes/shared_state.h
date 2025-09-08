/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:23:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 20:04:37 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_STATE
# define SHARED_STATE

# include "philo.h"

void		mutex_lock(t_mutex *mutex);
void		mutex_unlock(t_mutex *mutex);
__uint32_t	mutex_get_data(t_mutex *mutex);
void		mutex_set_data(t_mutex *mutex, __uint32_t data);
void		safe_printf(t_philo *philo, char *str, int mode);
#endif