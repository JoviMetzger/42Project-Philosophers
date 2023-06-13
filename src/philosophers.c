/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/13 14:18:55 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// - One or more philosophers sit at a round table.
// There is a large bowl of spaghetti in the middle of the table.
// - The philosophers alternatively eat, think, or sleep.
// While they are eating, they are not thinking nor sleeping;
// while thinking, they are not eating nor sleeping;
// and, of course, while sleeping, they are not eating nor thinking.
// - There are also forks on the table. There are as many forks as philosophers.
// - Because serving and eating spaghetti with only one fork is very inconvenient, a
// philosopher takes their right and their left forks to eat, one in each hand.
// - When a philosopher has finished eating, they put their forks back on the table and
// start sleeping. Once awake, they start thinking again. The simulation stops when
// a philosopher dies of starvation.
// - Every philosopher needs to eat and should never starve.
// - Philosophers don’t speak with each other.
// - Philosophers don’t know if another philosopher is about to die.
// - No need to say that philosophers should avoid dying!

// - Global variables are forbidden!
// - Your(s) program(s) should take the following arguments:
// (number_of_philosophers), (time_to_die time_to_eat), (time_to_sleep),
// ([number_of_times_each_philosopher_must_eat])

int main(int argc, char **argv)
{
    t_data data;
    
    //data = (t_data *)ft_calloc(sizeof(t_data), 1);
    if (argc >= 5) // && argc <= 6)
    {
        if (!ft_check_input(&data, argc, argv))
            ft_error_msg("Invalid Input");
        // if (!ft_init(data))
        //     ft_error_msg("Initializing problem");
        // if (!ft_threads(data))
        //    ft_error_msg("Something went wrong with the threads");
    }
    else
    {
        printf("Error:\n" GREEN BOLD "Try: " RESET "./philo " RED BOLD "<" RESET "number of philosophers" RED BOLD "> " RESET RED BOLD "<" RESET "time to die" RED BOLD "> " RESET RED BOLD "<" RESET "time to eat" RED BOLD "> " RESET RED BOLD "<" RESET "time to sleep" RED BOLD "> " RESET RED BOLD "<" RESET "number of times each philosopher must eat" RED BOLD ">\n" RESET);
        exit(EXIT_FAILURE);
    }
    return (0);
}