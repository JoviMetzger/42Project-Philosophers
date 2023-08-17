/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:06:30 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_unlock_forks();
 * 	- This function releases the forks held by a philosopher after 
 *	  they finish eating.
 *	- Depending on the philosopher's position (odd or even).
*/
static void	ft_unlock_forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

/* ft_eat();
 * 	- This function simulates a philosopher eating.
 *	- It first locks the necessary forks for the philosopher to eat. 
 *		- The order of locking depends on the philo's pos to prevent deadlocks.
 *	- It updates the philosopher's last_meal_time and eaten_meals count.
 *	- Then, it releases the forks by calling ft_unlock_forks().
*/
static void	ft_eat(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_write(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		ft_write(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_write(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		ft_write(philo, "has taken left fork");
	}
	pthread_mutex_lock(&philo->arg->monitoring_mutex);
	philo->last_meal_time = get_time();
	philo->eaten_meals += 1;
	pthread_mutex_unlock(&philo->arg->monitoring_mutex);
	ft_write(philo, "is eating");
	ft_wait(philo->arg->time_to_eat);
	ft_unlock_forks(philo);
}

/* ft_start_routine();
 * 	- This function represents the entry point for a philosopher's thread.
 *	- In the case of a single philosopher, 
 *	  it simply prints that the philosopher has taken a fork and returns.
 *	- In a loop, it repeatedly checks whether the program is done or not. 
 */
void	*ft_start_routine(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->arg->nb_philos == 1)
	{
		ft_write(philo, "has taken right fork");
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->arg->monitoring_mutex);
		if (philo->arg->is_done)
		{
			pthread_mutex_unlock(&philo->arg->monitoring_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->monitoring_mutex);
		ft_eat(philo);
		ft_write(philo, "is sleeping");
		ft_wait(philo->arg->time_to_sleep);
		ft_write(philo, "is thinking");
	}
	return (NULL);
}
