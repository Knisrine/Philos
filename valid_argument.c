/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:52:01 by nisrine           #+#    #+#             */
/*   Updated: 2025/08/16 21:06:46 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	is_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (is_number(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_argument(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (!is_valid(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
