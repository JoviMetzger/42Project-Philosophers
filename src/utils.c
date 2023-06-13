/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 08:11:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/13 14:09:21 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error_msg(char *msg)
{
    int i;
    i = -1;
    printf(RED "Error\n%s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

// void	*ft_calloc(size_t count, size_t n)
// {
// 	void	*ptr;

// 	ptr = (void *)malloc(count * n);
// 	if (!ptr)
// 		return (NULL);
// 	ft_bzero(ptr, count);
// 	return (ptr);
// }

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
