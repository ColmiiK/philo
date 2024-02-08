/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/08 16:52:25 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

Philo Routine()

The routine will be the function executed over and over by the philos, Basically ,I created a loop that will break as soon as the dead flag is 1, in other words as soon as a philo is dead. Remember:

The philosophers alternatively eat, sleep, or think. While they are eating, they are not thinking nor sleeping, while thinking, they are not eating nor sleeping, and, of course, while sleeping, they are not eating nor thinking.

So in our loop, they will eat, sleep and think. Let’s start with the easiest one when they think we just need to print a message “X is thinking” (X is the philo number), When they sleep we need to make them sleep the length of the input inserted by the user using our ft_usleep (described in the bottom of this page) and then print the message “X is sleeping”. Now to the eating part, We will lock the right fork first using pthread_mutex_lock and print the message, and do the same with the left fork. Then he will eat using ft_usleep again and only then he will drop the forks by unlocking the locks, before that we change some variables that give our monitor indications but that’s the general idea.

Monitor()

This thread will be running and monitoring the whole program, it has 2 checks in it that run infinitely until a philo dies or they all ate the number of meals they need to (last input argument). Basically, we will check that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating. If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. The other check is to see if all the philos finished eating the amount of meals they need to, and if they did we will again change the dead flag to one and break the threads loop.
*/

static int ft_wait(t_philo *philo, size_t ms, size_t meal_start)
{
	size_t i;


	i = 0;
	while (i < ms / 10)
	{
		ft_usleep(10);
		philo->last_meal = TIME - meal_start;
		if (*philo->dead)
			return (1) ;
		i++;
	}
	return (0);
}


static void ft_eating(t_philo *philo)
{
	size_t meal_start;
	
	meal_start = TIME;
	pthread_mutex_lock(philo->r_fork);
	printf("%zu %d has taken a fork\n", TIME, philo->id);
	if (philo->l_fork == NULL)
		return ;
	pthread_mutex_lock(philo->l_fork);
	printf("%zu %d has taken a fork\n", TIME, philo->id);
	
	philo->is_eating = true;
	printf("%zu %d is eating\n", TIME, philo->id);
	if (ft_wait(philo, philo->eat_ms, meal_start))
		return ;
	philo->is_eating = false;
	philo->last_meal = TIME - meal_start;
	philo->meals_eaten++;
		
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	*ft_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (*philo->dead == false)
	{
		// if (philo->id % 2 == 0)
		// 	ft_usleep(1);
		ft_usleep(philo->id);

		ft_eating(philo);
		if (*philo->dead == true)
			return NULL;

		printf("%zu %d is sleeping\n", TIME, philo->id);
		ft_usleep(philo->sleep_ms);
		if (*philo->dead == true)
			return NULL;

		printf("%zu %d is thinking\n", TIME, philo->id);
		if (*philo->dead == true)
			return NULL;
	}
	return NULL;
}

static void *ft_monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while (data->dead == false)
	{
		i = -1;
		while (++i < data->n_of_philos)
		{
			if (data->philo[i].is_eating == false && data->philo[i].last_meal > data->philo[i].die_ms)
			{
				data->dead = true;
				printf("%zu %d died\n", get_current_time() - data->philo[i].start_ms, data->philo[i].id);
			}
			if (data->philo[i].meals_eaten == data->philo[i].n_of_meals)
				data->dead = true;
		}
	}
	return (0);
}

static int	ft_threads(t_data *data, int n_of_philos)
{
	int	i;
	pthread_t monitor;

	i = -1;
	while (++i < n_of_philos)
		if (pthread_create(&data->philo[i].thread, NULL, &ft_routine, &data->philo[i]))
			{
				data->dead = true;
				return (1);
			}
	if (pthread_create(&monitor, NULL, &ft_monitor, data))
	{
		data->dead = true;
		return (1);
	}
	if (pthread_join(monitor, NULL))
		return (1);
	i = -1;
	while (++i < n_of_philos)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	return (0);
}

int	ft_philosophers(t_data **data, char **av)
{
	pthread_mutex_t forks[ft_atoi(av[1])];
	int i;

	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return (printf("Error: unable to malloc (data)\n"));
	if (ft_setup_struct(*data, av))
		return (printf("Error: unable to setup data\n"));
	if (ft_setup_mutex(*data, (*data)->n_of_philos, forks))
		return (printf("Error: unable to initialize mutexes\n"));
	if (ft_threads(*data, (*data)->n_of_philos))
		return (printf("Error: unable to create threads\n"));
	i = -1;
	while (++i < (*data)->n_of_philos)
		pthread_mutex_destroy(&forks[i]);
	return (0);
}
