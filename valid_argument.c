/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisrine <nisrine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:52:01 by nisrine           #+#    #+#             */
/*   Updated: 2025/07/28 14:58:05 by nisrine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_valid(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (is_number(arg[i]) == 1)
            return (0);
        i++;
    }
    return (1);
}

int valid_argument(char **arg)
{
    int i;

    i = 1;
    while(arg[i])
    {
        if (is_valid(arg[i]) == 0)
        {
            printf("Invalid argument: %s\n", arg[i]);
            return (0);
        }
        i++;
    }
    return (1);
}
