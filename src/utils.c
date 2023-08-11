/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/11 21:39:57 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* get_left_fork_pos();
 *	- This function is used to determine the position of the left fork 
 *	  for a philosopher to maintain proper synchronization.
 *	- Calculates the position of the left fork by subtracting 1 from 
 *	  the philosopher's current position.
 *	- If the calculated left position is less than 0 (it's the first philo),
 *	  it wraps around to the last philosopher's position by setting it 
 *	  to nb_philos - 1.
 */
int	get_left_fork_pos(int pos, int nb_philos)
{
	int	left;

	left = pos - 1;
	if (left < 0)
		left = nb_philos - 1;
	return (left);
}

/* set_state();
 *	- This function ensures that the philosopher's state is updated safely 
 *	  and consistently among multiple threads.
 *	- Locks the philosopher's update mutex using pthread_mutex_lock().
 *	- Updates the philosopher's state with the provided state.
 *	- Unlocks the philosopher's update mutex using pthread_mutex_unlock().
 */
void	set_state(t_philo *philos, int pos, t_state state)
{
	pthread_mutex_lock(&philos[pos].update);
	philos[pos].state = state;
	pthread_mutex_unlock(&philos[pos].update);
}

/* get_state();
 *	- This function retrieves the current state of a philosopher.
 *	- Retrieves the philosopher's state from the philos array at 
 *	 the specified position 'pos'.
 *	- Returns the retrieved state.
 */
t_state	get_state(t_philo *philos, int pos)
{
	t_state	state;

	state = philos[pos].state;
	return (state);
}

/* ft_wait();
 *	- This function simulates a waiting period for a specified amount of time.
 *	- Retrieves the current time using the get_time().
 *	- Enters a loop that continues until the desired time has passed.
 *	- The function repeatedly checks the difference between the current time 
 *	  and the start time against the desired waiting time.
 *	- If the desired waiting time has not passed, the function sleeps for 
 *	  a short period using usleep(100) and continues the loop.
 */
void	ft_wait(int time)
{
	long long	start;

	if (time <= 0)
		return ;
	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

/* get_time();
 *	- This function retrieves the current time in milliseconds. 
 *	- Retrieves the current time using the gettimeofday function,
 *	  which provides the current time with high precision.
 *	- Calculates the time in milliseconds by converting seconds 
 *	  to milliseconds and adding microseconds divided by 1000.
 */
long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}
