/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:19:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/13 14:12:39 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(char *num)
{
    int i;

    i = 0;
    while (num[i])
    {
        if (num[i] == '+')
            i++;
        if (num[i] >= '0' && num[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

int ft_check_input(t_data *data, int argc, char **argv)
{
    int i;
    
    i = 1;
    while (argv[i])
    {
        if (!ft_isdigit(argv[i]))
            return (0);
        i++;
    }
    data->nb_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->max_eat_count = ft_atoi(argv[5]);
    else 
        data->max_eat_count = 0; 
    return (1);
}
