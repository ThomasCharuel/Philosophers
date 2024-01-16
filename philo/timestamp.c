/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:02:55 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/16 22:04:23 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_timestamp_ms_diff(struct timeval a, struct timeval b)
{
	return (a.tv_sec * 1000 + a.tv_usec / 1000) - (b.tv_sec * 1000 + b.tv_usec / 1000);
}
