#include "../inc/philo.h"

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_m);
	if (get_time() - philo->info->start_time
		- philo->last_meal_t > philo->info->t_to_die)
		return (pthread_mutex_unlock(&philo->last_meal_m), 1);
	pthread_mutex_unlock(&philo->last_meal_m);
	return (0);
}

static void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->id]);
	print(*philo, TAKE_FORK);
	pthread_mutex_lock(&philo->info->forks[(philo->id + 1)
		% philo->info->number_of_philos]);
	print(*philo, TAKE_FORK);
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal_t = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->last_meal_m);
	print(*philo, EAT);
	sensitive_usleep(philo->info->t_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->id]);
	pthread_mutex_unlock(&philo->info->forks[(philo->id + 1)
		% philo->info->number_of_philos]);
	print(*philo, SLEEP);
	sensitive_usleep(philo->info->t_to_sleep);
	print(*philo, THINK);
	if (philo->info->number_of_philos % 2 != 0)
		sensitive_usleep(philo->info->t_to_eat / 2);
}

static void	*philos_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		sensitive_usleep(philo->info->t_to_eat / 2);
	while (philo->info->is_anyone_died == false)
	{
		philo_routine(philo);
		philo->meals_eaten++;
		if (philo->info->must_eat != -1
			&& philo->meals_eaten >= philo->info->must_eat)
			break ;
	}
	philo->had_enough = true;
	return (NULL);
}

int	create_philos(t_philo *philos, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		if (pthread_create(&philos[i].thread, NULL, &philos_life, &philos[i]))
			return (1);
	i = -1;
	while (++i < info->number_of_philos)
		pthread_join(philos[i].thread, NULL);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;
	int		count;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philos->info->number_of_philos)
		{
			if (check_death(&philos[i]))
			{
				philos->info->is_anyone_died = true;
				return (print(philos[i], DIE), NULL);
			}
			if (philos[i].had_enough == true)
				count++;
		}
		if (count == philos->info->number_of_philos)
			break ;
	}
	return (NULL);
}