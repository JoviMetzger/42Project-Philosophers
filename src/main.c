/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 22:00:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// system("leaks -q philo");

/* main();
 *	The function validates the command-line arguments,
 *	performs some initialization steps, and executes different actions 
 *	based on the arguments' validity.
 */
int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philos;
	t_fork		*forks;

	philos = NULL;
	forks = NULL;
	if (argc >= 5 && argc <= 6)
	{
		if (!ft_check_input(argv))
			ft_error_msg("Invalid Input");
		if (!init_arg(&arg, argc, argv))
			ft_error_msg("Something went wrong with the initialization");
		if (!ft_threads(&arg, philos, forks))
			ft_error_msg("Something went wrong with the threads");
	}
	else
	{
		printf("Error:\n"GREEN BOLD"Try: "RESET"./philo "RED BOLD "<"RESET
			"number of philosophers"RED BOLD"> "RESET RED BOLD"<"RESET"time "
			"to die"RED BOLD"> "RESET RED BOLD"<"RESET"time to eat"RED BOLD"> "
			RESET RED BOLD"<"RESET"time to sleep"RED BOLD"> "RESET RED BOLD"<"
			RESET"number of times each philosopher must eat"RED BOLD">\n"RESET);
	}
	return (0);
}
