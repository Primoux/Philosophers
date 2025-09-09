/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:23:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/09 01:13:19 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_STATE
# define SHARED_STATE

# include "philo.h"

void		mutex_lock(t_mutex *mutex);
void		mutex_unlock(t_mutex *mutex);
__int32_t	mutex_get_data(t_mutex *mutex);
void		mutex_set_data(t_mutex *mutex, __int32_t data);
void		safe_printf(t_philo *philo, char *str, int mode);
#endif