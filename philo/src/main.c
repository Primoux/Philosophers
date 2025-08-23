/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:47:53 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/23 16:47:54 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "style.h"

void	*thread_start(void *arg)
{
	(void)arg;
	printf("%sHello from the thread%s\n", GREEN, RST);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, thread_start, NULL);
	pthread_join(thread, NULL);
	printf("%sHello from the main%s\n", RED, RST);
	return (0);
}
