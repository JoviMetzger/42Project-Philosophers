/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/20 11:41:02 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_error_msg();
* 	Displays an error message with a specific error message 
*	and terminates the program.
*/
void	ft_error_msg(char *msg)
{
	printf(RED "Error\n%s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

long int get_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void ft_print_action(t_data *data, int philo_pos, char *msg)
{
	long int time;
	
	time = get_time() - data->start_time;
	pthread_mutex_lock(&(data->writing));
	if (!(data->stop_condition))
	{
		printf("%ld ", time);
		printf("%i ", philo_pos + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(data->writing));
}

long int	time_difference(long int past, long int pres)
{
	return (pres - past);
}

void ft_time_to_(long int time, t_data *data)
{
	long int i;

	i = get_time();
	while(!(data->stop_condition))
	{
		if (time_difference(i, get_time()) >= time)
			break ;
		usleep(50);
	}
}