/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:55 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 04:04:04 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h> 
# include <pthread.h>
# include <limits.h>
# include <stdbool.h> 
# include <sys/time.h>

// Colour code
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BOLD    "\033[1m"
# define RESET   "\033[0m"

typedef struct s_arg 
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_times_each_philo_must_eat;
	int					is_done;
	pthread_mutex_t		monitoring_mutex;
}	t_arg;

typedef struct s_philo 
{
	int					pos;
	int					eaten_meals;
	long long int		last_meal_time;
	long long int		start_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			t_id;
	t_arg				*arg;
}	t_philo;

int				ft_check_input(char **argv);

void			ft_error_msg(char *msg);
void			ft_write(t_philo *philo, char *msg);
long long int	ft_time(t_philo *philo);
long long int	get_time(void);
void			ft_wait(int n);

int				ft_atoi(char *str);
void			*ft_calloc(size_t count, size_t n);
void			ft_bzero(void *str, size_t n);

int				init_args(t_arg *arg, int argc, char **argv);
t_philo			*init_philos(t_arg *arg, pthread_mutex_t *forks_array);
pthread_mutex_t	*init_forks(t_arg *arg);

int				ft_threads(t_arg *arg, t_philo *philos, pthread_mutex_t *forks);
void			*ft_start_routine(void *_philo);
void			ft_destroy_mutex(t_arg *arg, pthread_mutex_t *forks, \
				t_philo *philos);

#endif
