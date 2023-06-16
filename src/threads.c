/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/16 12:58:18 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_threads(t_data *data)
{
	printf("yes\n");	//rm
	printf("nb_philo: %d\n", data->nb_philo);	//rm
	printf("time_to_die: %d\n", data->time_to_die);	//rm
	printf("time_to_eat: %d\n", data->time_to_eat);	//rm
	printf("time_to_sleep: %d\n", data->time_to_sleep);	//rm
	printf("max_eat_count: %d\n", data->max_eat_count);	//rm
	return (1); // If everything goes right
	// return (0); If something goes wrong
}
