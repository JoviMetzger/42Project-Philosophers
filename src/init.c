/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:16:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 20:29:03 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_arg	ft_init_arg(int argc, char **argv)
{
	t_arg	arg;

	arg.nb_philos = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg.nb_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		arg.nb_of_times_each_philo_must_eat = 0;
	return (arg);
}

static t_philo	*init_philos_list(t_arg arg)
{
	int		i;
	t_philo	*philos;

	philos = ft_calloc(arg.nb_philos, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < arg.nb_philos)
	{
		pthread_mutex_init(&(philos[i].fork), NULL);
		pthread_mutex_init(&(philos[i].update), NULL);
		philos[i].state = sleeping;
		philos->last_meal = 0;
	}
	return (philos);
}

/* ft_init();
*	This function initializes the t_data structure by assigning values 
*	to its fields based on command-line arguments, 
*	allocating memory for arrays, and calling other initialization functions. 
*	It returns 0 if there is an error during initialization, and 1 otherwise.
*/
int	ft_init(t_data *data, int argc, char **argv)
{	
	data->arg = ft_init_arg(argc, argv);
	printf("INIT - arg:\n");
	print_args(data->arg);
	data->philos = init_philos_list(data->arg);
	if (!data->philos)
	{
		free(data);
		return (0);
	}
	printf("INIT - philo:\n");
	return (1);
}


void	print_args(t_arg arg)
{
	printf("%d ", arg.nb_philos);
	printf("%d ", arg.time_to_die);
	printf("%d ", arg.time_to_eat);
	printf("%d ", arg.time_to_sleep);
	printf("%d\n", arg.nb_of_times_each_philo_must_eat);
}
