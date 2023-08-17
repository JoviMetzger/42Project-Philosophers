/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:06:04 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_dead();
 * 	- This function is responsible for checking if a philosopher is dead or not.
 *	- It first checks if a philosopher has reached the required number of meals.
 *	- Then, it calculates the time elapsed since the philosopher's last meal 
 *	  and compares it to the time_to_die value.
 *	- If the philosopher has exceeded the time_to_die, it prints a message.
 */
static int	ft_dead(t_arg *arg, t_philo *philo, int *satisfied_philos)
{
	if (arg->nb_of_times_each_philo_must_eat > 0 && \
		philo->eaten_meals >= arg->nb_of_times_each_philo_must_eat)
		*satisfied_philos += 1;
	if ((get_time() - philo->last_meal_time) >= philo->arg->time_to_die)
	{
		pthread_mutex_unlock(&arg->monitoring_mutex);
		ft_write(philo, RED"is dead"RESET);
		pthread_mutex_lock(&arg->monitoring_mutex);
		arg->is_done = 1;
		pthread_mutex_unlock(&arg->monitoring_mutex);
		return (1);
	}
	return (0);
}

/* monitoring();
 *	- This function is a continuous loop that monitors the philosophers' status.
 *	- It iterates through all philosophers and checks if any of them 
 *	  are dead using the ft_dead() function. 
 *	- If a philosopher is dead, it immediately returns(STOPS).
 *	- If all philosophers have satisfied their meal requirements, 
 *	  it prints a message.
 */
static void	monitoring(t_philo *philos, t_arg *arg)
{
	int	satisfied_philos;
	int	i;

	satisfied_philos = 0;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&arg->monitoring_mutex);
		while (++i < arg->nb_philos)
		{
			if (ft_dead(arg, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == arg->nb_philos)
		{
			arg->is_done = 1;
			printf("Every Philosopher had "GREEN"%d"RESET" meals!\n", \
				arg->nb_of_times_each_philo_must_eat);
			pthread_mutex_unlock(&arg->monitoring_mutex);
		}
		pthread_mutex_unlock(&arg->monitoring_mutex);
	}
}

/* ft_threads();
 * 	- This function initializes and manages the philosopher threads.
 *	- It creates threads using pthread_create().
 *	- Starts the monitoring process.
 *	- It waits for all philosopher threads to finish using pthread_join() 
 *	  and then cleans up resources.
 */
int	ft_threads(t_arg *arg, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < arg->nb_philos)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL, ft_start_routine, \
			(void *)&philos[i]) != 0)
			return (0);
	}
	monitoring(philos, arg);
	i = -1;
	while (++i < arg->nb_philos)
	{
		if (pthread_join(philos[i].t_id, NULL) != 0)
			return (0);
	}
	ft_destroy_mutex(arg, forks, philos);
	return (1);
}
