/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:55 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/13 14:07:59 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h> 
# include <pthread.h>
# include <limits.h>

// Colour code
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BOLD    "\033[1m"
# define RESET   "\033[0m"

struct s_data;

typedef struct s_philo
{
    int             ate_times;
    int             pos;
    int             left_fork_pos;
    int             right_fork_pos;
    unsigned long   last_meal;
    struct s_data   *data;    
    pthread_t       *thread_id;
} t_philo;

typedef struct s_data
{
    int             nb_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             max_eat_count;
    unsigned long   start_time;
    int             stop_condition;
    int             all_ate;
    pthread_mutex_t *forks;
    pthread_mutex_t meal_check;
    pthread_mutex_t writing;
    t_philo         *philos;
    
} t_data;

void	ft_error_msg(char *msg);
int ft_check_input(t_data *data, int argc, char **argv);
void	*ft_calloc(size_t count, size_t n); //rm
int	ft_atoi(const char *str);

#endif