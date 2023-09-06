/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 21:17:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* is_dead();
 * 	- This function is responsible for checking if a philosopher is still alive.
 */
int	is_dead(t_philo *phil)
{
	int	alive;

	pthread_mutex_lock(&(phil->arg->is_dead_mutex));
	alive = phil->arg->is_done;
	pthread_mutex_unlock(&(phil->arg->is_dead_mutex));
	return (alive);
}

/* take_fork();
 * 	- This function is responsible for checking if a philosopher is still alive.
 */
static void	take_fork(char fork_s, t_philo *philo)
{
	int		*taken;
	t_fork	*fork;

	if (!is_dead(philo))
	{
		taken = &(philo->right_taken);
		fork = philo->right_fork;
		if (fork_s == 'l')
		{
			taken = &(philo->left_taken);
			fork = philo->left_fork;
		}
		pthread_mutex_lock(&(fork->lock));
		if (!(*taken) && !fork->used)
		{
			*taken = 1;
			fork->used = 1;
			pthread_mutex_unlock(&(fork->lock));
			ft_write("has taken a fork", philo);
		}
		else
			pthread_mutex_unlock(&(fork->lock));
	}
}

/* unlock_forks();
 * 	- It locks the mutex of the corresponding fork, sets *taken to 0, 
 *	  and marks the fork as not used (used is set to 0).
*/
static void	unlock_forks(char fork_s, t_philo *phil)
{
	int		*taken;
	t_fork	*fork;

	taken = &(phil->right_taken);
	fork = phil->right_fork;
	if (fork_s == 'l')
	{
		taken = &(phil->left_taken);
		fork = phil->left_fork;
	}
	pthread_mutex_lock(&(fork->lock));
	*taken = 0;
	fork->used = 0;
	pthread_mutex_unlock(&(fork->lock));
}

/* release_forks_and_sleep();
 * 	- This function is responsible for releasing both the left and 
 *	  right forks held by a philosopher after they finish eating and 
 *	  then making the philosopher sleep.
*/
static void	release_forks_and_sleep(t_philo *phil)
{
	unlock_forks('r', phil);
	unlock_forks('l', phil);
	ft_write("is sleeping", phil);
	ft_wait(phil->arg->time_to_sleep);
}

/* ft_start_routine();
 * 	- This function represents the entry point for a philosopher's thread.
 *	- Depending on the philosopher's position (odd or even), 
 *	  it makes philosophers with odd positions wait for a short period of time.
 */
void	*ft_start_routine(void *_philo)
{
	t_philo		*philo;

	philo = (t_philo *)_philo;
	if (philo->pos % 2 != 0)
		ft_wait(philo->arg->time_to_eat);
	while (!is_dead(philo))
	{
		if (philo->meal_count >= philo->arg->nb_of_times_each_philo_must_eat
			&& philo->arg->nb_of_times_each_philo_must_eat > 0)
			break ;
		take_fork('l', philo);
		if (philo->left_taken)
			take_fork('r', philo);
		if (philo->right_taken && philo->left_taken)
		{
			ft_write("is eating", philo);
			ft_wait(philo->arg->time_to_eat);
			philo->meal_count++;
			pthread_mutex_lock(&(philo->last_meal_mutex));
			philo->last_meal = get_time() - philo->arg->start_time;
			pthread_mutex_unlock(&(philo->last_meal_mutex));
			release_forks_and_sleep(philo);
		}
	}
	return (NULL);
}
