/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:17:28 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/25 20:23:11 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "utils.h"
#include <unistd.h>

int	is_all_digits(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		if (write(STDERR_FILENO, "Error : empty arg\n", 19) == -1)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			if (write(STDERR_FILENO,
					"Error: invalid character in argument\n", 38) == -1)
				return (EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
