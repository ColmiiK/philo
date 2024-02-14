/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/14 11:37:21 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
/*
TODO:
All philos should eat n_of_meals times when specified, not just one philo

All tests:
./philo
./philo 1
./philo 1 2
./philo 1 2 3	Invalid argument / usage message.
./philo 4 500 abc 200	Invalid argument.
./philo 4 500 200 2.9	Invalid argument.
./philo 4 -500 200 200	Invalid argument.
./philo 4 2147483648 200 200	Invalid argument.
./philo 0 800 200 200	Invalid argument.
./philo 500 100 200 200	2 defensible solutions:
– Invalid argument. (ex. Max 200 philosophers)
– A philosopher dies at 100 ms.
./philo 4 2147483647 200 200	No one dies.
./philo 4 200 2147483647 200	A philosopher dies at 200 ms.
./philo 4 800 200 2147483647	A philosopher dies at 800 ms.
./philo 2 800 200 200	No one dies.
./philo 5 800 200 200	No one dies.
./philo 5 0 200 200	A philosopher dies at 0 ms.
./philo 5 800 0 200	No one dies.
./philo 5 800 200 0	No one dies.
./philo 5 800 0 0	No one dies.
./philo 5 800 200 200 0	2 defensible solutions:
– Invalid argument.
– Simulation stops immediately because everyone ate 0 times.
./philo 4 410 200 200	No one dies.
./philo 1 200 200 200	Philosopher 1 takes a fork and dies at 200 ms.
./philo 4 2147483647 0 0	No one dies.
./philo 4 200 210 200	A philosopher dies at 200 ms.
./philo 2 600 200 800	A philosopher dies at 600 ms.
./philo 4 310 200 200	A philosopher dies at 310 ms.
./philo 3 400 100 100 3	No one dies, each philosopher eats at least 3 times.
./philo 200 800 200 200 9	No one dies, each philosopher eats at least 9 times.
./philo 200 410 200 200	A philosopher dies at 410 ms.


Failed tests:
./philo 4 2147483648 200 200 (INT_MAX and INT_MIN)
./philo 4 200 2147483647 200
	Expected output: A philosopher dies at 200 ms.

*/
static void	ft_eat(t_philo *philo)
{
	philo->time = get_current_time() - (philo)->start_ms;
	pthread_mutex_lock(philo->r_fork);
	ft_printf_alive(philo, 'f');
	pthread_mutex_lock(philo->l_fork);
	ft_printf_alive(philo, 'f');
	philo->meal_duration = get_current_time() - (philo)->start_ms - philo->time;
	ft_printf_alive(philo, 'e');
	ft_wait(philo, get_current_time() - (philo)->start_ms, philo->eat_ms);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;
	size_t	sleep_start;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(2);
	while (*philo->dead == false)
	{
		ft_eat(philo);
		if (*philo->dead == true)
			return (NULL);
		sleep_start = get_current_time() - (philo)->start_ms;
		ft_printf_alive(philo, 's');
		ft_wait(philo, sleep_start, philo->sleep_ms);
		if (*philo->dead == true)
			return (NULL);
		ft_printf_alive(philo, 't');
	}
	return (NULL);
}

static void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->dead == false)
	{
		i = -1;
		while (++i < data->n_of_philos)
		{
			if (data->philo[i].r_fork == data->philo[i].l_fork)
				data->dead = true;
			if (data->philo[i].meal_duration
				+ data->philo[i].eat_ms > data->philo[i].die_ms)
				data->dead = true;
			if (data->philo[i].n_of_meals == -1)
				;
			else if (data->philo[i].meals_eaten >= data->philo[i].n_of_meals) // ALL philos need to eat this amount for the program to finish, not just one
			{
				data->dead = true;
				return (NULL);
			}
			if (data->dead == true)
			{
				ft_usleep(2);
				ft_printf_alive(&data->philo[i], 'd');
				break ;
			}
		}
	}
	return (NULL);
}

static int	ft_threads(t_data *data, int n_of_philos)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < n_of_philos)
		if (pthread_create(&data->philo[i].thread, NULL,
				&ft_routine, &data->philo[i]))
			data->dead = true;
	if (pthread_create(&monitor, NULL, &ft_monitor, data))
		data->dead = true;
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
	pthread_mutex_t	*forks;
	int				i;

	*data = (t_data *)malloc(sizeof(t_data));
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(av[2]));
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
