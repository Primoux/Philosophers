/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_state.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:54:47 by enchevri          #+#    #+#             */
/*   Updated: 2025/10/02 21:27:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_STATE_H
# define SHARED_STATE_H

# include "philo.h"

__uint32_t	mutex_get_data(t_mutex *mutex);
void		mutex_set_data(t_mutex *mutex, __uint32_t state);
int			safe_printf(t_philo *philo, char *str);
int			mutex_compare_and_swap(t_mutex *mutex, __uint32_t state);
__int32_t	get_min(__int32_t time1, __int32_t time2);
int			check_own_death(t_philo *philo);
int			finished_meal(t_philo *philo);
__uint32_t	get_min_u32(__uint32_t a, __uint32_t b);

#endif
