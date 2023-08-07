/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 18:06:49 by jmetzger      ########   odam.nl         */
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

// void ft_free(t_data *data) ////
// {
// 	int i;

// 	i = -1;
// 	while (++i < data->arg->nb_philos)
// 	{
// 		while (get_state(data->philos, i) != freed)
// 			usleep(1000);
// 		pthread_mutex_destroy(&(data->philos[i].fork));
// 		pthread_mutex_destroy(&(data->philos[i].update));
// 	}
// 	free(data->philos);
// }


int	get_left_fork_pos(int pos, int nb_philos)
{
	int	left;

	left = pos - 1;
	if (left < 0)
		left = nb_philos - 1;
	return (left);
}

void	set_state(t_philo *philos, int pos, t_state state)
{
	pthread_mutex_lock(&philos[pos].update);
	philos[pos].state = state;
	pthread_mutex_unlock(&philos[pos].update);
}

t_state	get_state(t_philo *philos, int pos)
{
	t_state	state;

	state = philos[pos].state;
	return (state);
}

void	ft_wait(int time)
{
	long long	start;

	if (time <= 0)
		return ;
	start = get_time();
	while (get_time() - start < time)
		usleep(1000);
}

long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}
