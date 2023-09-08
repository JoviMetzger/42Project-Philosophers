/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 14:43:01 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_write();
 * 	Writes the state of the Philosopher (EAT, SLEEP, THINK, FORK).
 */
void	ft_write(char *msg, t_philo *philo)
{
	long	cur_time;

	cur_time = get_time() - philo->arg->start_time;
	pthread_mutex_lock(&(philo->arg->monitoring_mutex));
	if (!is_dead(philo))
		printf("%09ld %d %s\n", cur_time, philo->pos + 1, msg);
	pthread_mutex_unlock(&(philo->arg->monitoring_mutex));
}

/* get_time();
 * 	Get the current time.
 */
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* ft_wait();
 * 	A delay for a specified amount of time in milliseconds,
 *	using a busy-wait loop with 1-millisecond intervals.
 */
void	ft_wait(long int value)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < value)
		usleep(100);
}

/* ft_error_msg();
 * 	Displays an error message with a specific error message 
 *	and terminates the program.
 */
int	ft_error_msg(char *msg)
{
	printf(RED "Error\n%s\n" RESET, msg);
	return (EXIT_FAILURE);
}

/* ft_free_all();
 * 	Frees all the allocated memory.
 */
int	ft_free_all(t_philo *philos, t_fork *forks)
{
	free(philos);
	free(forks);
	return (0);
}
