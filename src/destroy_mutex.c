/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mutex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 20:02:17 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_destroy_mutex(t_philo *philos, t_arg arg)
{
	int	i;

	i = -1;
	while (++i < arg.nb_philos)
	{
		while (get_state(philos, i) != freed)
			usleep(1000);
		pthread_mutex_destroy(&(philos[i].fork));
		pthread_mutex_destroy(&(philos[i].update));
	}
	free(philos);
}


void ft_destroy(t_data *data)
{
    if (data->philos)
    {
        ft_destroy_mutex(data->philos, data->arg);
        free(data->philos);
    }
    free(data);
}