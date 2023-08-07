/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 19:15:33 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_start_philo(t_data *data, t_philo *philos, t_arg arg, int pos)
{
	pthread_t	thread;

	data->arg = arg;
	data->philos = philos;
	data->pos = pos;
	data->philos[pos].last_meal = get_time();
	if (pthread_create(&thread, NULL, &ft_start_routine, data))
		return (1);
	pthread_detach(thread);
	return (0);
}

static int	ft_start(t_data *data, t_philo *philos, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.nb_philos)
	{
		if (ft_start_philo(data, philos, arg, i))
			return (1);
		i += 2;
		if (i % 2 == 0 && i >= arg.nb_philos)
			i = 1;
	}
	return (0);
}

int ft_threads(t_data *data)
{
	ft_start(data, data->philos, data->arg);
	printf("TEST 1:\n"); //RM
	check_meals(data->philos, data->arg);
	printf("TEST 2:\n"); //RM
	ft_destroy_mutex(data->philos, data->arg);
	printf("TEST 3:\n"); //RM
	ft_wait(1);
	printf("TEST 4:\n"); //RM
	return (1);
}

