/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:28:56 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/08 12:28:46 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/* 

Philo routine:
When the philosophers are doing a task (eating, sleeping, thinking), print "X is (task)", where X is the number of the philospher
	when thinking, print "X is thinking"
	when sleeping, print "X is sleeping", using the time in ms from the input
	when eating, lock the right fork first, then the left fork, then print "X is eating" using the time in ms from the input, then unlock both forks

Monitor:
Infinite loop until a philosopher dies or they all eat the number of meals indicated in the input, if it's present
	Check if last_meal > die_ms, if true then set bool dead = true, break the loops and end execution
	
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

*/

void	ft_debug(t_data *data)
{
	printf("die_ms: %ld\n", data->philo[0].die_ms);
	printf("eat_ms: %ld\n", data->philo[0].eat_ms);
	printf("sleep_ms: %ld\n", data->philo[0].sleep_ms);
	printf("total_meals: %d\n", data->philo[0].n_of_meals);
}

static int	ft_are_args_valid(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (printf("Error: incorrect number of arguments\n"));
	if (ft_are_args_valid(av))
		return (printf("Error: invalid argument(s)\n"));
	ft_philosophers(&data, av);
	// ft_debug(data);
	ft_annihilation(data);
}
