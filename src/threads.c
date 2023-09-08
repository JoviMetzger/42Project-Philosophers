/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 21:16:43 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_create_philos();
 * 	This function is responsible for creating and 
 *	initializing philosopher and fork objects.
 */
static int	ft_create_philos(t_philo **philos, t_fork **forks, t_arg *arg)
{
	int	i;

	*philos = ft_calloc(arg->nb_philos, sizeof(t_philo));
	if (!(*philos))
		return (0);
	*forks = ft_calloc(arg->nb_philos, sizeof(t_fork));
	if (!(*forks))
	{
		free(*philos);
		return (0);
	}
	i = 0;
	while (i < arg->nb_philos)
	{
		init_philo(&(*philos)[i], forks, arg, i);
		i++;
	}
	return (1);
}

/* ft_create_threads();
 * 	This function is responsible for creating threads for each philosopher 
 *	and a monitoring thread to observe the state of the philosophers.
 */
static int	ft_create_threads(t_philo **philos, t_arg *arg)
{
	int	i;

	arg->start_time = get_time();
	i = 0;
	while (i < arg->nb_philos)
	{
		if (pthread_create(&((*philos)[i].thread), NULL,
			ft_start_routine, &((*philos)[i])))
			return (0);
		i++;
	}
	if (pthread_create(&(arg->death_thread), NULL,
			monitoring, philos))
		return (0);
	return (1);
}

/* ft_join_threads();
 * 	This function is responsible for waiting 
 *	for all philosopher threads to finish.
 */
static int	ft_join_threads(t_philo **philos, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philos)
	{
		if (pthread_join((*philos)[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

/* ft_threads();
 *	This function is the start of the program.
 *		- First creates philosophers and forks.
 *		- Then creates threads for philosophers and monitoring. 
 *		- Waits for all threads to finish.
 *		- At last we free allocated memory. 
 */
int	ft_threads(t_arg *arg, t_philo *philos, t_fork *forks)
{
	if (!ft_create_philos(&philos, &forks, arg))
		return (0);
	if (!ft_create_threads(&philos, arg))
		return (0);
	if (!ft_join_threads(&philos, arg))
		return (0);
	return (1);
}
