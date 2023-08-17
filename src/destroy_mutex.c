/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mutex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:00:11 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_destroy_mutex();
 * 	Destroies the mutexes and frees the structs.
 */
void	ft_destroy_mutex(t_arg *arg, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	if (arg)
		pthread_mutex_destroy(&arg->monitoring_mutex);
	if (forks)
	{
		i = -1;
		while (++i < arg->nb_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
		}
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}
