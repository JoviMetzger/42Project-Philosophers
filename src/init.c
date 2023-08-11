/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/11 20:38:52 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_init_arg();
*	- This function initializes the t_data structure with the provided 
*	  command-line arguments.
*	- It assigns the values of the arguments to the corresponding fields 
*	  in the t_arg structure.
*	- Allocates memory for an array of t_philo structures.
*		- Initializes mutexes for each philosopher's fork and update.
*/
int	ft_init_arg(int argc, char **argv, t_data *data)
{
	int	i;

	data->arg.nb_philos = ft_atoi(argv[1]);
	data->arg.time_to_die = ft_atoi(argv[2]);
	data->arg.time_to_eat = ft_atoi(argv[3]);
	data->arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->arg.nb_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		data->arg.nb_of_times_each_philo_must_eat = -1;
	data->philos = ft_calloc(data->arg.nb_philos, sizeof(t_philo));
	if (!data->philos)
		return (0);
	i = -1;
	while (++i < data->arg.nb_philos)
	{
		pthread_mutex_init(&(data->philos[i].fork), NULL);
		pthread_mutex_init(&(data->philos[i].update), NULL);
		data->philos[i].state = sleeping;
	}
	return (1);
}
