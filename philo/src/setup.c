/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:37:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/08 12:46:56 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_setup_struct(t_data *data, char **av)
{
	int i;

	data->n_of_philos = ft_atoi(av[1]);
	if (data->n_of_philos > 200 || data->n_of_philos == 0)
		return (1);
	data->philo = (t_philo *)ft_calloc(data->n_of_philos, sizeof(t_philo));
	if (!data->philo)
		return (1);
	i = -1;
	data->dead = false;
	while (++i < data->n_of_philos)
	{
		data->philo[i].start_ms = i + 1; 
		data->philo[i].die_ms = ft_atoi(av[2]);
		data->philo[i].eat_ms = ft_atoi(av[3]);
		data->philo[i].sleep_ms = ft_atoi(av[4]);
		data->philo[i].meals_eaten = 0;
		data->philo[i].start_ms = get_current_time();
		data->philo[i].last_meal = 0;
		if (av[5])
			data->philo[i].n_of_meals = ft_atoi(av[5]);
		else
			data->philo[i].n_of_meals = -1;
	}
	return (0);
}

static int	ft_calloc_mutexes(t_data *data, int n_of_philos,
	pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < n_of_philos)
	{
		data->philo[i].r_fork = &forks[i];
		if (i == n_of_philos - 1)
			data->philo[i].l_fork = &forks[0];
		else
			data->philo[i].l_fork = &forks[i + 1];
		data->philo[i].write_lock = &data->write_lock;
		data->philo[i].dead_lock = &data->dead_lock;
		data->philo[i].meal_lock = &data->meal_lock;
		data->philo[i].dead = &data->dead;
		data->philo[i].id = i;
	}
	return (0);
}

int	ft_setup_mutex(t_data *data, int n_of_philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->n_of_philos)
		if (pthread_mutex_init(&forks[i], NULL))
			return (1);
	if (ft_calloc_mutexes(data, n_of_philos, forks))
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	return (0);
}
