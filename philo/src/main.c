/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:28:56 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/29 15:35:08 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/* 
Data parse:
A valid input looks like this
./philo 5 800 200 200 7
where
5 -> number of philosophers
800 -> time in ms for a philosopher to die if they haven't eaten
200 -> time in ms that it takes for a philosopher to eat
200 -> time in ms that it takes for a philosopher to sleep
7 -> number of times all philosophers need to eat before terminating the program (OPTIONAL ARGUMENT)
Check if there are all numbers greater than 0, otherwise exit
Store the info in the struct for later referencing

Mutex:
Before each philo can access a lock, pthread_mutex_lock(&mutex) so all other philos have to wait for it
Once the philo is over using the fork, pthread_mutex_unlock(&mutex) so the other philos can resume eating, assuming they're not dead

Needed data in struct:
each philo
typedef struct s_philo
{
	pthread_t thread;
	int		id;
	bool	is_eating;
	int		meals;
	size_t	last_meal;
	size_t	die_ms;
	size_t	eat_ms;
	size_t	sleep_ms;
	size_t	start_ms;
	pthread_mutex_t *fork_r;
	pthread_mutex_t *fork_l;
	
	
	
}	t_philo

typedef struct s_data
{
	bool	dead;
	t_philo *philo
	
}	t_data

Data initialization:
Store data in struct
Initialize mutexes

Philo routine:
When the philosophers are doing a task (eating, sleeping, thinking), print "X is (task)", where X is the number of the philospher
	when thinking, print "X is thinking"
	when sleeping, print "X is sleeping", using the time in ms from the input
	when eating, lock the right fork first, then the left fork, then print "X is eating" using the time in ms from the input, then unlock both forks

Monitor:
Infinite loop until a philosopher dies or they all eat the number of meals indicated in the input, if it's present
	Check if last_meal > die_ms, if true then set bool dead = true, break the loops and end execution
	
*/

int	main(int ac, char **av)
{
	
}
