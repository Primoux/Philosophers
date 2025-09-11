/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:23:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/11 04:40:58 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_STATE
# define SHARED_STATE

# include "philo.h"

__uint32_t	mutex_get_data(t_mutex *mutex);
void		mutex_set_data(t_mutex *mutex, __int32_t data);
int			safe_printf(t_philo *philo, char *str);
int			mutex_compare_and_swap(t_mutex *mutex, __uint32_t state);
__int32_t	get_min(__int32_t time1, __int32_t time2);
int			check_own_death(t_philo *philo);
int			finished_meal(t_philo *philo);
#endif
