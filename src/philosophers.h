/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:55 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 21:22:21 by jmetzger      ########   odam.nl         */
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
	long				start_time;
	pthread_mutex_t		monitoring_mutex;
	pthread_mutex_t		is_dead_mutex;
	pthread_t			death_thread;
}	t_arg;

typedef struct s_fork
{
	int					used;
	pthread_mutex_t		lock;
}	t_fork;

typedef struct s_philo
{
	int					pos;
	int					meal_count;
	int					right_taken;
	int					left_taken;
	long				last_meal;
	t_fork				*right_fork;
	t_fork				*left_fork;
	pthread_t			thread;
	pthread_mutex_t		last_meal_mutex;
	t_arg				*arg;
}	t_philo;

//lbft_utils
int				ft_atoi(char *str);
void			*ft_calloc(size_t count, size_t n);
void			ft_bzero(void *str, size_t n);

//uitls
int				ft_error_msg(char *msg);
int				ft_free_all(t_philo *philos, t_fork *forks);
void			ft_wait(long int value);
void			ft_write(char *msg, t_philo *philo);
long			get_time(void);

//main functions
int				ft_check_input(char **argv);
int				is_dead(t_philo *phil);
int				ft_threads(t_arg *arg, t_philo *philos, t_fork *forks);
int				init_arg(t_arg *params, int argc, char **argv);
void			init_philo(t_philo *phil, t_fork **forks, t_arg *arg, int pos);
void			*ft_start_routine(void *_philo);
void			*monitoring(void *_philo);

#endif
