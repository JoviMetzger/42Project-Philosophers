/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 08:28:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* main();
*	The function performs some initialization steps,
*	validates the command-line arguments, and executes different actions 
*	based on the arguments' validity. If the arguments are invalid, 
*	it displays an error message and exits the program.
*/
int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (argc >= 5 && argc <= 6)
	{
		if (!ft_check_input(argv))
			ft_error_msg("Invalid Input");
		if (!ft_init(data, argc, argv))
			ft_error_msg("Initializing problem");
		if (!ft_threads(data))
			ft_error_msg("Something went wrong with the threads");
	}
	else
	{
		printf("Error:\n" GREEN BOLD "Try: " RESET "./philo " RED BOLD "<" \
				RESET "number of philosophers" RED BOLD "> " RESET RED BOLD \
				"<" RESET "time to die" RED BOLD "> " RESET RED BOLD "<" \
				RESET "time to eat" RED BOLD "> " RESET RED BOLD "<" RESET \
				"time to sleep" RED BOLD "> " RESET RED BOLD "<" RESET \
				"number of times each philosopher must eat" RED \
				BOLD ">\n" RESET);
		exit(EXIT_FAILURE);
	}
	return (0);
}
