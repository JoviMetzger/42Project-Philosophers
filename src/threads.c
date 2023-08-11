/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/11 22:32:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_start();
 *	- This function starts multiple threads to represent the philosophers. 
 *	- Iterates over the philosophers and starts a thread for each philosopher.
 *		- Allocates memory for a t_data structure and initializes its fields.
 *		- Creates a new thread using pthread_create() 
 *		- and passes the ft_start_routine() along with the data struct.
 *		- Detaches the created thread using pthread_detach() to ensure 
 *		  the thread's are automatically released when it finishes execution.
 *	- After starting the threads for even-numbered philosophers, 
 *	  the function resets the iteration index to 1, ensuring that odd-numbered 
 *	  philosophers are also covered.
 */
static int	ft_start(t_philo *philos, t_arg arg)
{
	int			i;
	t_data		*data;
	pthread_t	thread;

	i = 0;
	while (i < arg.nb_philos)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			return (1);
		data->arg = arg;
		data->philos = philos;
		data->pos = i;
		philos[i].last_meal = get_time();
		if (pthread_create(&thread, NULL, &ft_start_routine, data))
			return (1);
		pthread_detach(thread);
		i = i + 2;
		if (i % 2 == 0 && i >= arg.nb_philos)
			i = 1;
	}
	return (1);
}

/* ft_threads();
 *	- This function coordinates the execution of philosopher threads 
 *	  and handles their termination. 
 *	- ft_start() to start threads for philosophers.
 *	- check_meals() to ensure that each philosopher has eaten 
 *	  the required number of times.
 *	- ft_destroy_mutex() to destroy mutexes.
 *	- ft_wait(1) to wait for all philosopher threads to complete.
*/
int	ft_threads(t_philo *philos, t_arg arg)
{
	if (!ft_start(philos, arg))
		return (0);
	if (!check_meals(philos, arg))
		return (0);
	ft_destroy_mutex(philos, arg);
	ft_wait(1);
	return (1);
}
