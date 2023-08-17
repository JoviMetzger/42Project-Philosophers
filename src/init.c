/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:00:30 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* init_forks();
 * 	Initialize the mutexes/forks.
 */
pthread_mutex_t	*init_forks(t_arg *arg)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = ft_calloc(arg->nb_philos, sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	i = 0;
	while (i < arg->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (forks);
}

/* init_philos();
 * 	Initialize the philo struct.
 */
t_philo	*init_philos(t_arg *arg, pthread_mutex_t *forks_array)
{
	t_philo	*philos;
	int		i;

	philos = ft_calloc(arg->nb_philos, sizeof(t_philo));
	if (!philos)
		return (0);
	i = 0;
	while (i < arg->nb_philos)
	{
		philos[i].pos = i + 1;
		philos[i].eaten_meals = 0;
		philos[i].left_fork = &forks_array[i];
		philos[i].right_fork = &forks_array[(i + 1) % arg->nb_philos];
		philos[i].last_meal_time = get_time();
		philos[i].arg = arg;
		i++;
	}
	return (philos);
}

/* init_args();
 * 	Initialize the arg struct.
 */
int	init_args(t_arg *arg, int argc, char **argv)
{
	arg->nb_philos = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->nb_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		arg->nb_of_times_each_philo_must_eat = -1;
	arg->is_done = 0;
	if (pthread_mutex_init(&arg->monitoring_mutex, NULL))
		return (0);
	return (1);
}
