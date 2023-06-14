/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 09:18:48 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_init_mutex();
*	This function initializes mutexes for each fork, as well as 
*	two additional mutexes (meal_check and writing) in the t_data structure. 
*	It returns 1 if there is an error during initialization, and 0 otherwise.
*		- The pthread_mutex_init() initialize the mutex corresponding to 
*		  the i-th fork, meal_check, writing. 
*		- The NULL argument is passed as the second argument, 
*		  indicating default attributes for the mutex.
*		- If the pthread_mutex_init function returns a non-zero value, 
*		  it means an error occurred during initialization. 
*		  In such a case, the function returns 1 to indicate the error.
*/
static int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init((&data->meal_check), NULL))
		return (1);
	if (pthread_mutex_init((&data->writing), NULL))
		return (1);
	return (0);
}

/* ft_init_philos();
*	The function initializes the philosopher structures in the t_data structure. 
*	It assigns values to various fields of each philosopher.
*	It returns 0 to indicate successful initialization.
*/
static int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].pos = i;
		data->philos[i].ate_times = 0;
		data->philos[i].left_fork_pos = i;
		data->philos[i].right_fork_pos = (i + 1) % data->nb_philo;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

/* ft_init();
*	This function initializes the t_data structure by assigning values 
*	to its fields based on command-line arguments, 
*	allocating memory for arrays, and calling other initialization functions. 
*	It returns 0 if there is an error during initialization, and 1 otherwise.
*/
int	ft_init(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat_count = ft_atoi(argv[5]);
	else
		data->max_eat_count = 0;
	data->stop_condition = 0;
	data->all_ate = 0;
	data->forks = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), \
			data->nb_philo);
	data->philos = (t_philo *)ft_calloc(sizeof(t_philo), data->nb_philo);
	if (ft_init_philos(data))
		return (0);
	if (ft_init_mutex(data))
		return (0);
	return (1);
}
