/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:55:17 by yakdik            #+#    #+#             */
/*   Updated: 2023/08/09 17:06:07 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

/*TYPEDEFS*/
typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

/*STRUCTS*/
struct					s_philo
{
	int id;         // filozofun id'si
	int had_enough; // filozof doydu mu
	int					meals_eaten;
	time_t last_meal_t;          // filozof'un son yemek yedigi zaman
	pthread_mutex_t last_meal_m; // son yemek'in mutex
	pthread_t thread;            // filozofun threadi
	t_info *info;                // info structi
};

// alttaki info yapisi masada olan bitenler hakkinda genel bilgilendirici olarak dusunulebilir

struct					s_info
{
	int number_of_philos;        // filozof sayisi
	int must_eat;                // filozofun kac kere yemek yemesi gerektigi
	bool is_anyone_died;         // filozoflardan biri olmus mu
	time_t t_to_die;             // filozofun olmesi icin gerekli zaman
	time_t t_to_eat;             // filozofun yemek icin gerekli zaman
	time_t t_to_sleep;           // filozofun uyumak icin gerekli zaman
	time_t start_time;           // programin basladigi zaman
	pthread_mutex_t *forks;      // tum catallar icin mutex array
	pthread_mutex_t print_mutex; // mutexlerin dogru print edilmesi icin
};

/*FUNCTIONS*/
time_t					get_time(void);
void					print(t_philo philo, char *str);
void					sensitive_usleep(time_t time);
int						ft_atoi(const char *str);
void					clean_up(pthread_t *monitor_thread, t_philo *philos);

int						create_philos(t_philo *philos, t_info *info);
void					*monitor(void *arg);
#endif
