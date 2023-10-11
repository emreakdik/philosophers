/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:30:35 by yakdik            #+#    #+#             */
/*   Updated: 2023/10/09 01:21:55 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_death(t_philo *philo, int which)
{
	if (which == 1)
	{
		pthread_mutex_lock(&philo->last_meal_m);
		pthread_mutex_lock(&philo->had_enough_m);
		if (philo->had_enough == false && get_time() - philo->info->start_time
			- philo->last_meal_t > philo->info->t_to_die)
			return (pthread_mutex_unlock(&philo->had_enough_m),
				pthread_mutex_unlock(&philo->last_meal_m), 1);
		pthread_mutex_unlock(&philo->last_meal_m);
		pthread_mutex_unlock(&philo->had_enough_m);
	}
	else if (which == 0)
	{
		pthread_mutex_lock(&philo->info->is_anyone_died_m);
		if (philo->info->is_anyone_died == false)
			return (pthread_mutex_unlock(&philo->info->is_anyone_died_m), 1);
		pthread_mutex_unlock(&philo->info->is_anyone_died_m);
	}
	return (0);
}

static void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->id]);
	print_and_kill(*philo, TAKE_FORK, 0);
	pthread_mutex_lock(&philo->info->forks[(philo->id + 1)
		% philo->info->number_of_philos]);
	print_and_kill(*philo, TAKE_FORK, 0);
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal_t = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->last_meal_m);
	print_and_kill(*philo, EAT, 0);
	sensitive_usleep(philo->info->t_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->id]);
	pthread_mutex_unlock(&philo->info->forks[(philo->id + 1)
		% philo->info->number_of_philos]);
	print_and_kill(*philo, SLEEP, 0);
	sensitive_usleep(philo->info->t_to_sleep);
	print_and_kill(*philo, THINK, 0);
	if (philo->info->number_of_philos % 2 != 0)
		sensitive_usleep(philo->info->t_to_eat / 2);
}

static void	*philos_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		sensitive_usleep(philo->info->t_to_eat / 2);
	while (check_death(philo, 0))
	{
		philo_routine(philo);
		philo->meals_eaten++;
		if (philo->info->must_eat != -1
			&& philo->meals_eaten == philo->info->must_eat)
			break ;
	}
	pthread_mutex_lock(&philo->had_enough_m);
	philo->had_enough = true;
	pthread_mutex_unlock(&philo->had_enough_m);
	return (NULL);
}

void	create_philos(t_philo *philos, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		pthread_create(&philos[i].thread, NULL, &philos_life, &philos[i]);
	i = -1;
	while (++i < info->number_of_philos)
		pthread_join(philos[i].thread, NULL);
}

void	*monitor(void *arg)
{
	int			i;
	int			count;
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		count = 0;
		while (++i < philos->info->number_of_philos)
		{
			if (check_death(&philos[i], 1))
				return (print_and_kill(philos[i], DIE, 1), NULL);
			pthread_mutex_lock(&philos[i].had_enough_m);
			if (philos[i].had_enough == true)
				count++;
			pthread_mutex_unlock(&philos[i].had_enough_m);
		}
		if (count == philos->info->number_of_philos)
			break ;
	}
	return (NULL);
}
