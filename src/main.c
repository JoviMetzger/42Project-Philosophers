/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/12 11:54:16 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// //___________________________________________
// // FOR LEAKS
// void ft_systemleaks(void)
// {
//     system("leaks -q philo");
// }
// //  - atexit(ft_systemleaks); // USE FOR LEAKS
// //____________________________________________

/* ft_error_msg();
* 	Displays an error message with a specific error message 
*	and terminates the program.
*/
void	ft_error_msg(char *msg)
{
	printf(RED "Error\n%s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

/* main();
*	The function performs some initialization steps,
*	validates the command-line arguments, and executes different actions 
*	based on the arguments' validity. If the arguments are invalid, 
*	it displays an error message and exits the program.
*/
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc >= 5 && argc <= 6)
	{
		if (!ft_check_input(argv))
			ft_error_msg("Invalid Input");
		if (!ft_init_arg(argc, argv, &data))
		{
			ft_error_msg("Invalid Argument");
			return (1);
		}
		if (!ft_threads(data.philos, data.arg))
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
	}
	return (0);
}
