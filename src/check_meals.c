/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_meals.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/12 11:41:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_kill_all();
 *	- This function is responsible for "killing" all philosophers by updating 
 *	  their states to "dead" if they are not already in a "freed" state.
 *	- Iterates through each philosopher using a loop.
 *	- Locks the philosopher's update mutex to modify its state.
 *	- If the philosopher's state is not "freed," it updates their state 
 *	  to "dead."
 *	- Unlocks the philosopher's update mutex.
 */
static void	ft_kill_all(t_philo *philos, int nb_philos)
{
	int	i;

	i = -1;
	while (++i < nb_philos)
	{
		pthread_mutex_lock(&philos[i].update);
		if (philos[i].state != freed)
			philos[i].state = dead;
		pthread_mutex_unlock(&philos[i].update);
	}
}

/* should_philo_be_killed();
 *	- This function checks if a philosopher should be "killed" 
 *	  due to exceeding the time allowed for not eating.
 *	- Checks if the philosopher's state is "freed." 
 *		- If so, increments the count of "freed" philosophers 
 *		  and returns 0 (indicating no killing necessary).
 *	- Compares the difference between the current time and the last time 
 *	  the philosopher ate with the time_to_die threshold. 
 *		- If the difference is greater than time_to_die, it indicates that 
 *		  the philo has exceeded the time allowed without eating 
 *		  and should be "killed."
 *	- Prints a message indicating that the philosopher has died, 
 *	  updates their state to "dead," and locks their update mutex 
 *	  to perform the state update.
 *	- Returns 1 to indicate that the philosopher has been killed.
 */
static int	should_philo_be_killed(t_philo *philos, int time_to_die, \
	int pos, int *freed_pos)
{
	int				killed;
	long long int	time_since_last_meal;

	killed = 0;
	if (get_state(philos, pos) == freed)
		(*freed_pos)++;
	else
	{
		pthread_mutex_lock(&philos[pos].update);
		time_since_last_meal = get_time() - philos[pos].last_meal;
		if (time_since_last_meal > time_to_die)
		{
			printf("%lld %d died\n", get_time(), pos + 1);
			killed = 1;
			philos[pos].state = dead;
			pthread_mutex_unlock(&philos[pos].update);
		}
		else
			pthread_mutex_unlock(&philos[pos].update);
	}
	return (killed);
}

/* check_meals();
 *	- This function checks if all philosophers have finished eating 
 *	  the required number of times or if any philosopher has exceeded 
 *	  the time limit for not eating.
 *	- Enters a loop that continues until all philosophers are freed or 
 *	  the check is_done (to indicate whether the check is complete).
 *	- Iterates through each philosopher using a loop and calls 
 *	  should_philo_be_killed() to determine if a philosopher should be killed 
 *	  based on the time limit.
 *	- Updates is_done based on the result of should_philo_be_killed().
 *	- Calls ft_kill_all() to mark all philosophers as dead 
 *	  if the check is complete.
 */
int	check_meals(t_philo *philos, t_arg arg)
{
	int	i;
	int	freed;
	int	is_done;

	freed = 0;
	is_done = 0;
	while (freed < arg.nb_philos && !is_done)
	{
		i = -1;
		freed = 0;
		while (++i < arg.nb_philos && !is_done)
			is_done = should_philo_be_killed(philos, arg.time_to_die, \
				i, &freed);
	}
	ft_kill_all(philos, arg.nb_philos);
	return (1);
}
