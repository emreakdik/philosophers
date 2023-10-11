/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:31:19 by yakdik            #+#    #+#             */
/*   Updated: 2023/10/09 01:25:57 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000 + time.tv_sec * 1000));
}

void	print_and_kill(t_philo philo, char *str, int kill)
{
	if (kill)
	{
		pthread_mutex_lock(&philo.info->is_anyone_died_m);
		philo.info->is_anyone_died = true;
		pthread_mutex_unlock(&philo.info->is_anyone_died_m);
	}
	pthread_mutex_lock(&philo.info->is_anyone_died_m);
	if ((philo.had_enough == false && philo.info->is_anyone_died == false)
		|| kill == 1)
	{
		pthread_mutex_lock(&philo.info->print_mutex);
		printf("%ld %d %s\n", get_time() - philo.info->start_time, philo.id + 1,
			str);
		pthread_mutex_unlock(&philo.info->print_mutex);
	}
	pthread_mutex_unlock(&philo.info->is_anyone_died_m);
}

void	sensitive_usleep(time_t time)
{
	time_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
		usleep(200);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

void	clean_up(pthread_t *monitor_thread, t_philo *philos)
{
	int	i;

	pthread_join(*monitor_thread, NULL);
	i = -1;
	while (++i < philos->info->number_of_philos)
	{
		pthread_mutex_destroy(&philos[i].last_meal_m);
		pthread_mutex_destroy(&philos[i].info->forks[i]);
	}
	pthread_mutex_destroy(&philos[0].info->print_mutex);
	free(philos->info->forks);
	free(philos);
}
