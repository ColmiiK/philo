/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:59:28 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/31 14:02:36 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			is_eating;
	int				meals;
	size_t			last_meal;
	size_t			start_ms;
	bool			dead;
	pthread_mutex_t	*r_fork_lock;
	pthread_mutex_t	*l_fork_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;

}					t_philo;

typedef struct s_data
{
	bool			dead;
	size_t			die_ms;
	size_t			eat_ms;
	size_t			sleep_ms;
	size_t			total_meals;
	t_philo			*philo;
}					t_data;

// Definitely not libft
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t n, size_t size);
int					ft_usleep(size_t ms);
// Parsing & Setup
int					ft_are_args_valid(char **av);
int					ft_setup_struct(t_data *data, char **av);
int					ft_setup_mutex(t_data *data, int n_of_philos);
// Program
int					ft_philosophers(t_data **data, char **av);
// Cleanup
void				ft_annihilation(t_data *data);

#endif