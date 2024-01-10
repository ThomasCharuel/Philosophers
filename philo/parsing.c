/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:42:22 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/10 18:52:57 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoui(char *s)
{
	unsigned int	res;
	size_t			i;

	res = 0;
	i = 0;
	while (s[i])
	{
		res = 10 * res + s[i] - 48;
		i++;
	}
	return (res);
}
