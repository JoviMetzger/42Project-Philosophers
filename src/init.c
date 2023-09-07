/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 21:13:30 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* init_philo();
 * 	Initialize the philo struct.
 */
void	init_philo(t_philo *philo, t_fork **forks, t_arg *arg, int pos)
{
	philo->arg = arg;
	philo->pos = pos;
	philo->last_meal = 0;
	philo->meal_count = 0;
	philo->right_taken = 0;
	philo->left_taken = 0;
	philo->right_fork = &((*forks)[pos]);
	if (pos == arg->nb_philos - 1)
		philo->left_fork = &((*forks)[0]);
	else
		philo->left_fork = &((*forks)[pos + 1]);
	philo->left_fork->used = 0;
	pthread_mutex_init(&(philo->last_meal_mutex), NULL);
	pthread_mutex_init(&(philo->left_fork->lock), NULL);
}

/* init_args();
 * 	Initialize the arg struct.
 */
int	init_arg(t_arg *arg, int argc, char **argv)
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
	pthread_mutex_init(&(arg->monitoring_mutex), NULL);
	pthread_mutex_init(&(arg->is_dead_mutex), NULL);
	return (1);
}
