/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/12 18:09:51 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_time();
 *	- To get the timestamp of current milliseconds.
 *		- start time - current time.
 */
long long int	ft_time(t_data *data)
{
	long long int	result;

	result = get_time() - data->start_time;
	return (result);
}

/* ft_eat();
 *	- This function represents the action of a philosopher eating. 
 *	- Retrieves the position of the left fork using get_left_fork_pos().
 *	- Checks if the philosopher is already in a dead state. 
 *		- If so, it releases the left fork and returns.
 *	- Prints a message indicating that the philosopher has taken a fork.
 *	- Locks the philosopher's own fork mutex to acquire the fork.
 *	- If the philosopher is not in a dead state, prints another message 
 *	  indicating that the philosopher has taken a second fork.
 *	- Locks the philosopher's update mutex to update its state 
 *	  and 'last_meal' time.
 *	- If the philosopher is not in a dead state, 
 *	  updates philos state to "eating" and records the 'last_meal' time.
 *	- Unlocks the update mutex and prints a message indicating that 
 *	  the philosopher is eating.
 *	- Calls ft_wait to simulate the time the philosopher spends eating.
 *	- Releases the philosopher's own fork and the left fork.
 */
static void	ft_eat(t_data *all)
{
	int	left_pos;

	left_pos = get_left_fork_pos(all->pos, all->arg.nb_philos);
	if (get_state(all->philos, all->pos) == dead)
	{
		pthread_mutex_unlock(&all->philos[left_pos].fork);
		return ;
	}
	printf("%lld %d has taken a fork\n", ft_time(all), all->pos + 1);
	pthread_mutex_lock(&all->philos[all->pos].fork);
	if (get_state(all->philos, all->pos) != dead)
		printf("%lld %d has taken a fork\n", ft_time(all), all->pos + 1);
	pthread_mutex_lock(&all->philos[all->pos].update);
	if (all->philos[all->pos].state != dead)
	{
		all->philos[all->pos].state = eating;
		all->philos[all->pos].last_meal = get_time();
		pthread_mutex_unlock(&all->philos[all->pos].update);
		printf("%lld %d is eating\n", ft_time(all), all->pos + 1);
		ft_wait(all->arg.time_to_eat);
	}
	else
		pthread_mutex_unlock(&all->philos[all->pos].update);
	pthread_mutex_unlock(&all->philos[all->pos].fork);
	pthread_mutex_unlock(&all->philos[left_pos].fork);
}

/* ft_action_and_print();
 *	- This function handles various philosopher actions and prints 
 *	  corresponding messages. 
 *	- If the philosopher is eating or in a stop state:
 *		- If the philosopher has eaten more than once, it prints a message 
 *		  indicating that the philosopher is thinking.
 *		- It waits until the left fork is available.
 *		- Locks the philosopher's update mutex to check its state and 
 *		  avoid potential conflicts.
 *		- If the philosopher is in a dead state, it unlock the update mutex
 *		  and returns.
 *		- Updates the philosopher's state to "thinking" and releases 
 *		  the update mutex.
 *		- Locks the left fork mutex and calls ft_eat() to simulate eating.
 *		- If the philosopher is in a sleeping state:
 *			- Prints a message indicating that the philosopher is sleeping.
 */
static void	ft_action_and_print(t_data *data, t_state state, \
	int ate_howmany_times)
{
	if (state == eating || state == stop)
	{
		if (ate_howmany_times > 1)
			printf("%lld %d is thinking\n", ft_time(data), data->pos + 1);
		pthread_mutex_lock(&data->philos[data->pos].update);
		while (get_state(data->philos, get_left_fork_pos(data->pos, \
			data->arg.nb_philos)) == thinking)
			usleep(500);
		pthread_mutex_unlock(&data->philos[data->pos].update);
		pthread_mutex_lock(&data->philos[data->pos].update);
		if (data->philos[data->pos].state != dead)
			data->philos[data->pos].state = thinking;
		pthread_mutex_unlock(&data->philos[data->pos].update);
		pthread_mutex_lock(&data->philos[get_left_fork_pos(data->pos, \
			data->arg.nb_philos)].fork);
		ft_eat(data);
	}
	else if (state == sleeping)
	{
		printf("%lld %d is sleeping\n", ft_time(data), data->pos + 1);
		ft_wait(data->arg.time_to_sleep);
	}
}

/* ft_philo_state();
 *	- This function determines the philosopher's next state based on 
 *	  its current state and the number of times it has eaten. 
 *	- Locks the philosopher's update mutex to check its state and 
 *	  update 'ate_how_many_times'.
 *	- If the philosopher is in a 'dead' state or the required number of 
 *	  meals has been reached (or no specific number of meals is required), 
 *	  it sets the state to "dead."
 *	- If the philosopher is currently eating, it updates the state to sleeping.
 *	- If the philosopher is allowed to continue eating, it increments 
 *	  the "ate_how_many_times" counter and sets the state to "eating."
 *	- If the philosopher is not in any of the above conditions, 
 *	  it sets the state to "stop."
 *	- After determining the next state, it calls ft_action_and_print() 
 *	  to handle the action and print corresponding messages.
 */
static t_state	ft_philo_state(t_data *data, int *ate_howmany_times)
{
	t_state	state;

	pthread_mutex_lock(&data->philos[data->pos].update);
	if (data->philos[data->pos].state == dead
		|| !data->arg.nb_of_times_each_philo_must_eat)
		state = dead;
	else if (data->philos[data->pos].state == eating)
	{
		data->philos[data->pos].state = sleeping;
		state = sleeping;
	}
	else if (0 > data->arg.nb_of_times_each_philo_must_eat
		|| (*ate_howmany_times)++
		< data->arg.nb_of_times_each_philo_must_eat - 1)
		state = eating;
	else
		state = stop;
	pthread_mutex_unlock(&data->philos[data->pos].update);
	ft_action_and_print(data, state, *ate_howmany_times);
	return (state);
}

/* ft_start_routine();
 *	- This function is the entry point for the threads representing individual 
 *	  philosophers. 
 *	- If the philosopher's position is odd, it calls ft_wait(3) 
 *	  to introduce an initial delay for better synchronization.
 *	- Enters a loop that continues until the philosopher is in a 
 *	  "dead" or "stop" state:
 *		- If there is only one philosopher, it simulates a minimal wait 
 *		  and retrieves the philosopher's state.
 *		- Otherwise, it calls ft_philo_state() to determine the next state
 *		  based on the philosopher's current state and meals consumed.
 */
void	*ft_start_routine(void *data)
{
	int		ate_howmany_times;
	int		pos;
	t_philo	*philos;
	t_state	state;

	philos = ((t_data *)data)->philos;
	pos = ((t_data *)data)->pos;
	ate_howmany_times = 0;
	state = sleeping;
	if (pos % 2 != 0)
		ft_wait(3);
	while (state != dead && state != stop)
	{
		if (((t_data *)data)->arg.nb_philos == 1)
		{
			usleep(250);
			state = get_state(philos, pos);
		}
		else
			state = ft_philo_state((t_data *)data, &ate_howmany_times);
	}
	free(data);
	set_state(philos, pos, freed);
	return (NULL);
}
