/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 18:32:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 18:10:59 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eat(t_data *data)
{
	int	left_pos;

	left_pos = get_left_fork_pos(data->pos, data->arg.nb_philos);
	if (get_state(data->philos, data->pos) == dead)
	{
		pthread_mutex_unlock(&data->philos[left_pos].fork);
		return ;
	}
	printf("%lld %d has taken a fork\n", get_time(), data->pos + 1);
	pthread_mutex_lock(&data->philos[data->pos].fork);
	if (get_state(data->philos, data->pos) != dead)
		printf("%lld %d has taken a fork\n", get_time(), data->pos + 1);
	pthread_mutex_lock(&data->philos[data->pos].update);
	if (data->philos[data->pos].state != dead)
	{
		data->philos[data->pos].state = eating;
		data->philos[data->pos].last_meal = get_time();
		pthread_mutex_unlock(&data->philos[data->pos].update);
		printf("%lld %d is eating\n", get_time(), data->pos + 1);
		ft_wait(data->arg.time_to_eat);
	}
	else
		pthread_mutex_unlock(&data->philos[data->pos].update);
	pthread_mutex_unlock(&data->philos[data->pos].fork);
	pthread_mutex_unlock(&data->philos[left_pos].fork);
}

static void	ft_action_and_print(t_data *data, t_state state, int ate_howmany_times)
{
	if (state == eating || state == stop)
	{
		if (ate_howmany_times > 1)
			printf("%lld %d is thinking\n", get_time(), data->pos + 1);
		while (get_state(data->philos, get_left_fork_pos(data->pos,
					data->arg.nb_philos)) == thinking)
			usleep(500);
		pthread_mutex_lock(&data->philos[data->pos].update);
		if (data->philos[data->pos].state == dead)
		{
			pthread_mutex_unlock(&data->philos[data->pos].update);
			return ;
		}
		data->philos[data->pos].state = thinking;
		pthread_mutex_unlock(&data->philos[data->pos].update);
		pthread_mutex_lock(&data->philos[get_left_fork_pos(data->pos,
				data->arg.nb_philos)].fork);
		ft_eat(data);
	}
	else if (state == sleeping)
	{
		printf("%lld %d is sleeping\n", get_time(), data->pos + 1);
		ft_wait(data->arg.time_to_sleep);
	}
}

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