/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:55 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/07 20:02:56 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h> 
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

// Colour code
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BOLD    "\033[1m"
# define RESET   "\033[0m"

typedef enum e_state
{
	eating,
	sleeping,
	thinking,
	dead,
	stop,
	freed,
}	t_state;

typedef struct s_philo
{
	t_state			state;
	pthread_mutex_t	update;
	pthread_mutex_t	fork;
	long long int 	last_meal;

}	t_philo;

typedef struct s_arg
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_each_philo_must_eat;
}	t_arg;


typedef struct s_data
{
	int				pos;
	t_arg			arg;
	t_philo			*philos;
}	t_data;

void	print_args(t_arg arg);
void ft_destroy(t_data *data);

int				ft_check_input(char **argv);
int				ft_init(t_data *data, int argc, char **argv);
int				ft_threads(t_data *data);
int				ft_atoi(const char *str);
int				get_left_fork_pos(int pos, int nb_philos);
void			*ft_start_routine(void *data);
void			check_meals(t_philo *philos, t_arg arg);
void			ft_destroy_mutex(t_philo *philos, t_arg arg);
void			*ft_calloc(size_t count, size_t n);
void			ft_bzero(void *str, size_t n);
void			ft_error_msg(char *msg);
void			ft_wait(int time);
void			set_state(t_philo *philos, int pos, t_state state);
long long int	get_time(void);
t_state			get_state(t_philo *philos, int pos);

#endif

