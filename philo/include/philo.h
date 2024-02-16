/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:59:28 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/16 16:49:03 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEAD_MSG "\033[0;31m%zu %d died\n\033[0m"
# define FORK_MSG "\033[0;33m%zu %d has taken a fork\n\033[0m"
# define EAT_MSG "\033[0;32m%zu %d is eating\n\033[0m"
# define THNK_MSG "\033[0;34m%zu %d is thinking\n\033[0m"
# define SLP_MSG "\033[0;35m%zu %d is sleeping\n\033[0m"

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			time;
	size_t			die_ms;
	size_t			eat_ms;
	size_t			sleep_ms;
	size_t			start_ms;
	size_t			meal_duration;
	int				n_of_philos;
	int				n_of_meals;
	bool			*dead;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

}					t_philo;

typedef struct s_data
{
	bool			dead;
	int				n_of_philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philo;
}					t_data;

// Definitely not libft
int					ft_isdigit(int c);
long				ft_atol(const char *str);
void				*ft_calloc(size_t n, size_t size);
size_t				get_current_time(void);
int					ft_usleep(size_t ms);
void				ft_printf_alive(t_philo *philo, char code);
int					ft_wait(t_philo *philo, size_t start, size_t ms);
bool				ft_is_meal_done(t_data *data);
int					ft_flag_check(t_philo *philo);
void				ft_flag_change(t_data *data);
// Parsing & Setup
int					ft_are_args_valid(char **av);
int					ft_setup_struct(t_data *data, char **av);
int					ft_setup_mutex(t_data *data, int n_of_philos,
						pthread_mutex_t *forks);
// Thread creation and routines
int					ft_initialization(t_data **data, char **av);
void				*ft_philos(void *arg);
void				*ft_monitor(void *arg);
int					ft_edge_case_fork(t_data *data, int i);
int					ft_edge_case_dead(t_data *data, int i);
// Cleanup
void				ft_annihilation(t_data *data);

#endif