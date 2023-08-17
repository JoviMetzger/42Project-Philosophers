/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 09:19:34 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:00:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_isdigit();
 *	Checks if a string represents a valid positive integer.
 *	Input 0 isn't valid.
 */
static int	ft_isdigit(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '0')
		return (0);
	while (num[i])
	{
		if (num[0] == '+')
			i++;
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

/* ft_check_input();
 *	This function uses ft_isdigit() to validate 
 *	all command-line arguments except the program name.
 */
int	ft_check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
