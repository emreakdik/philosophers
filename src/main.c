/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:31:16 by yakdik            #+#    #+#             */
/*   Updated: 2023/10/09 01:23:55 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	one_philo(t_info *info)
{
	printf("%d %d %s\n", 0, 1, TAKE_FORK);
	sensitive_usleep(info->t_to_die);
	printf("%ld %d %s\n", info->t_to_die + 1, 0, DIE);
	free(info->forks);
}

static int	init_info(t_info *info, int ac, char **av)
{
	info->number_of_philos = ft_atoi(av[1]);
	info->t_to_die = ft_atoi(av[2]);
	info->t_to_eat = ft_atoi(av[3]);
	info->t_to_sleep = ft_atoi(av[4]);
	info->must_eat = -1;
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	info->start_time = get_time();
	info->is_anyone_died = false;
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->number_of_philos);
	if (!info->forks)
		return (0);
	if (info->number_of_philos == 0)
		return (free(info->forks), write(2, "Error\n", 6), 0);
	if (!init_info_helper(info))
		return (free(info->forks), 0);
	return (1);
}

static int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (write(2, "Error: wrong number of arguments\n", 35), 1);
	j = 1;
	while (av[j] && av[j][i] >= '0' && av[j][i] <= '9')
	{
		i++;
		if (!av[j][i])
		{
			j++;
			i = 0;
		}
	}
	if (av[j])
		return (write(2, "Error: Parameters must be positive\n", 35), 1);
	return (0);
}

static int	init_philos(t_philo *philos, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
	{
		philos[i].id = i;
		philos[i].info = info;
		philos[i].last_meal_t = info->start_time;
		philos[i].meals_eaten = 0;
		if (pthread_mutex_init(&philos[i].had_enough_m, NULL))
			return (0);
		if (pthread_mutex_init(&philos[i].last_meal_m, NULL))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo		*philos;
	t_info		info;
	pthread_t	monitor_thread;

	if (check_args(ac, av) || !init_info(&info, ac, av))
		return (0);
	philos = (t_philo *)malloc(sizeof(t_philo) * info.number_of_philos);
	if (!philos)
		return (0);
	if (info.number_of_philos == 1)
		return (one_philo(&info), free(philos), 1);
	if (!init_philos(philos, &info)
		|| pthread_create(&monitor_thread, NULL, &monitor, philos))
		return (free(info.forks), free(philos), 0);
	create_philos(philos, &info);
	return (clean_up(&monitor_thread, philos), 0);
}
