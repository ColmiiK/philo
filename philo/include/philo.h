/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:59:28 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/29 15:58:02 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef	struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			is_eating;
	int				meals;
	size_t			last_meal;
	size_t			die_ms;
	size_t			eat_ms;
	size_t			sleep_ms;
	size_t			start_ms;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;

}					t_philo;

typedef struct s_data
{
	bool			dead;
	t_philo			*philo;
}					t_data;


int	ft_isdigit(int c);


# endif