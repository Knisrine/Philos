/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikhtib <nikhtib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:56:34 by nikhtib           #+#    #+#             */
/*   Updated: 2025/08/15 18:01:27 by nikhtib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     small_atoi(char *s)
{
    int result;
    int i;
    
    i = 0;
    result = 0;
    while (s[i])
    {
        result = result * 10 + (s[i] - 48);
        i++;
    }
    return (result);   
}