/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:55 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/05/31 13:44:11 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h> 

//Colour code
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BOLD    "\033[1m"
# define RESET   "\033[0m"


void	ft_error(char *msg);

#endif