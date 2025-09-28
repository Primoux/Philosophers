/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:02:14 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/28 22:19:16 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif
# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

# include "philo.h"

int		is_all_digits(const char *str);
int		ft_atoi(const char *str, int *error);
void	cleanup_resources(t_sim_data *sim_data);
void	cleanup_philo_threads(t_sim_data *sim_data, int count);

#endif
