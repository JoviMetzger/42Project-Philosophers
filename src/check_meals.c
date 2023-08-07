/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_meals.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 18:12:04 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

static int	ft_kill_philo(t_philo *philos, int time_to_die, int pos, int *freed_pos)
{
	int			killed;

	killed = 0;
	if (get_state(philos, pos) == freed)
		(*freed_pos)++;
	else
	{
		if (get_time() - philos[pos].last_meal > time_to_die)
		{
			printf("%lld %d died\n", get_time(), pos + 1);
			killed = 1;
			pthread_mutex_lock(&philos[pos].update);
			philos[pos].state = dead;
			pthread_mutex_unlock(&philos[pos].update);
		}
	}
	return (killed);
}


void	check_meals(t_philo *philos, t_arg arg)
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
			is_done = ft_kill_philo(philos, arg.time_to_die, i, &freed);
	}
	ft_kill_all(philos, arg.nb_philos);
}
