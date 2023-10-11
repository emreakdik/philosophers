/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:55:17 by yakdik            #+#    #+#             */
/*   Updated: 2023/10/09 01:24:10 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct					s_philo
{
	int					id;
	int					had_enough;
	int					meals_eaten;
	time_t				last_meal_t;
	pthread_mutex_t		had_enough_m;
	pthread_mutex_t		last_meal_m;
	pthread_t			thread;
	t_info				*info;
};

struct					s_info
{
	int					number_of_philos;
	int					must_eat;
	bool				is_anyone_died;
	time_t				t_to_die;
	time_t				t_to_eat;
	time_t				t_to_sleep;
	time_t				start_time;
	pthread_mutex_t		is_anyone_died_m;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
};

time_t					get_time(void);
void					print_and_kill(t_philo philo, char *str, int kill);
void					sensitive_usleep(time_t time);
int						ft_atoi(const char *str);
void					clean_up(pthread_t *monitor_thread, t_philo *philos);

void					create_philos(t_philo *philos, t_info *info);
void					*monitor(void *arg);
int						init_info_helper(t_info *info);
#endif
