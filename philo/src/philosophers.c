/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/13 17:46:14 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
			else if (data->philo[i].meals_eaten >= data->philo[i].n_of_meals)
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
