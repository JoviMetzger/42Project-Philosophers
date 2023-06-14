/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 09:24:06 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_error_msg();
* 	Displays an error message with a specific error message 
*	and terminates the program.
*/
void	ft_error_msg(char *msg)
{
	int	i;

	i = -1;
	printf(RED "Error\n%s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

/* ft_calloc();
*	Allocates memory for the given input and initializes all bytes to 0.
*/
void	*ft_calloc(size_t count, size_t n)
{
	void	*ptr;

	ptr = (void *)malloc(count * n);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}

/* ft_bzero();
*	Sets all bytes of a given memory block to 0.
*/
void	ft_bzero(void *str, size_t n)
{
	unsigned char	*dest;
	unsigned int	i;

	dest = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}

/* ft_atoi();
*	Converts a string representation of an integer to an integer value.
*	It skips leading whitespaces and allows for an optional '+' sign.
*	If the input isn't between MAX_INT and MIN_INT,
*	it will throw an error and terminates the program.
*/
int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	long	end;

	result = 0;
	sign = 1;
	while ((*str == ' ') || (*str == '\f')
		|| (*str == '\n') || (*str == '\r')
		|| (*str == '\t') || (*str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	end = result * sign;
	if (end > INT_MAX || end < INT_MIN)
		ft_error_msg("Invalid Input");
	return (result * sign);
}
