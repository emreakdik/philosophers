/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:47:04 by yakdik            #+#    #+#             */
/*   Updated: 2023/10/09 01:03:12 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_info_helper(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i++], NULL))
			return (0);
	}
	if (pthread_mutex_init(&info->is_anyone_died_m, NULL))
		return (0);
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (0);
	return (1);
}
