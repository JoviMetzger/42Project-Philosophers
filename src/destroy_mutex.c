/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mutex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/11 21:44:39 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_destroy_mutex();
 *	- While it iterates through each philosopher.
 *		- While the philosopher's state is not "freed," 
 *		  it repeatedly sleeps for a short period to wait for the philosopher 
 *		  to be freed (killed or finished eating).
 *	- After the philosopher is freed, it destroys the mutexes associated with 
 *	  the philosopher's fork and update using pthread_mutex_destroy.
 *	- Frees the memory allocated for the philosopher array using free.
 */
void	ft_destroy_mutex(t_philo *philos, t_arg arg)
{
	int	i;

	i = -1;
	while (++i < arg.nb_philos)
	{
		while (get_state(philos, i) != freed)
			usleep(100);
		pthread_mutex_destroy(&(philos[i].fork));
		pthread_mutex_destroy(&(philos[i].update));
	}
	free(philos);
}
