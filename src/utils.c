/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:05:05 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_write();
 * 	Writes the state of the Philosopher (EAT, SLEEP, THINK, FORK, DEAD).
 */
void	ft_write(t_philo *philo, char *msg)
{
	long long int	timestamp;

	pthread_mutex_lock(&philo->arg->monitoring_mutex);
	if (philo->arg->is_done)
	{
		pthread_mutex_unlock(&philo->arg->monitoring_mutex);
		return ;
	}
	timestamp = get_time() - philo->start_time;
	printf("%lld %d %s\n", timestamp, philo->pos, msg);
	pthread_mutex_unlock(&philo->arg->monitoring_mutex);
}

/* get_time();
 * 	Get the current time.
 */
long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* ft_wait();
 * 	A delay for a specified amount of time in milliseconds,
 *	using a busy-wait loop with 1-millisecond intervals.
 */
void	ft_wait(int value)
{
	long long	start;

	start = get_time();
	while (get_time() - start < value)
		usleep(1000);
}

/* ft_error_msg();
 * 	Displays an error message with a specific error message 
 *	and terminates the program.
 */
void	ft_error_msg(char *msg)
{
	printf(RED "Error\n%s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

/* ft_time();
 *	- To get the timestamp of current milliseconds.
 *		- start time - current time.
 */
long long int	ft_time(t_philo *philo)
{
	long long int	result;

	result = get_time() - philo->start_time;
	return (result);
}
