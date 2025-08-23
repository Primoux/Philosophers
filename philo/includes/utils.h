/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:02:14 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/23 23:51:12 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif
# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 0
# endif

enum	e_bool
{
	FALSE,
	TRUE
};

int		is_all_digits(const char *str);
int		ft_atoi(const char *str, int *error);

#endif
