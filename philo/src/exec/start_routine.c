/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:56:50 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 20:48:56 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"
#include <unistd.h>

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	printf("%s%s[%d]\tJe vie c'est cool la vie%s\n", BOLD, GREEN, philo->id,
		RST);
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
	pthread_mutex_lock(&philo->sim_data->start_mutex);
	while (philo->sim_data->start_flag == 0)
	{
		pthread_mutex_unlock(&philo->sim_data->start_mutex);
		pthread_mutex_lock(&philo->sim_data->print_mutex);
		printf("%s%s[%d]\tJ'attend c'est chiant%s\n", BOLD, MAGENTA, philo->id,
			RST);
		pthread_mutex_unlock(&philo->sim_data->print_mutex);
		usleep(5000);
		pthread_mutex_lock(&philo->sim_data->start_mutex);
	}
	pthread_mutex_unlock(&philo->sim_data->start_mutex);
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	printf("%s%s[%d]\tEnfin le monde est si vaste et je dispose de la fork G[%d] D[%d]%s\n",
		BOLD, RED, philo->id, philo->left_fork->id, philo->right_fork->id, RST);
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
	return (NULL);
}
