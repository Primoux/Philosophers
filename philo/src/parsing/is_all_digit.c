/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:17:28 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/24 01:09:58 by enchevri         ###   ########lyon.fr   */
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
		write(2, "Error : empty arg\n", 19);
		return (EXIT_FAILURE);
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			write(2, "error: invalid character in argument\n", 38);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
