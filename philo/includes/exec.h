/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:01:00 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/17 17:30:43 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "philo.h"

void	*start_routine(void *arg);
int		start_simulation(t_sim_data *sim_data);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
int		eating(t_philo *philo);


#endif