/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:17:28 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 00:36:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_all_digits(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
