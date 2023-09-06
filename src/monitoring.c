/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 21:43:00 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* check_philo_death();
 *	- This function checks if a philosopher has died and 
 *    updates the number of satisfied philosophers.
 */
static int	check_philo_death(t_philo *philo, long curr_time)
{
	int	last_meal;

	if (philo->arg->nb_of_times_each_philo_must_eat > 0 && \
		philo->meal_count >= philo->arg->nb_of_times_each_philo_must_eat)
		philo->arg->satisfied_philos += 1;
	pthread_mutex_lock(&(philo->last_meal_mutex));
	last_meal = curr_time - philo->last_meal;
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	if (last_meal > philo->arg->time_to_die)
	{
		pthread_mutex_lock(&(philo->arg->monitoring_mutex));
		pthread_mutex_lock(&(philo->arg->is_dead_mutex));
		philo->arg->is_done = 1;
		pthread_mutex_unlock(&(philo->arg->is_dead_mutex));
		printf("%09ld %d "RED"died\n"RESET, curr_time, philo->pos + 1);
		pthread_mutex_unlock(&(philo->arg->monitoring_mutex));
		return (1);
	}
	return (0);
}

/* monitoring();
 *	- This function is responsible for monitoring the state of the philosophers
 *    in a continuous loop.
 *  - It iterates through all philosophers and checks if any of them have died
 *    or if all have satisfied their meal requirements.
 *  - For each philosopher, it calls check_philo_death() to check if the philosopher 
 *    has died or satisfied their meal requirement.
 */
void	*monitoring(void *_philo)
{
	t_arg	*arg;
	t_philo	**philos;
	long	curr_time;
    int     i;

	philos = (t_philo **)_philo;
	arg = philos[0]->arg;
	while (1)
	{
		i = 0;
		curr_time = get_time() - arg->start_time;
		while (i < arg->nb_philos)
		{
			if (check_philo_death(&(*philos)[i], curr_time))
				return (NULL);
			i++;
		}
		// if (arg->satisfied_philos == arg->nb_philos)
		// {
		// 	arg->is_done = 1;
		// 	printf("Every Philosopher had "GREEN"%d"RESET" meals!\n", \
		// 		arg->nb_of_times_each_philo_must_eat);
		// }
		ft_wait(1);
	}
	return (NULL);
}
