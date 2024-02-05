/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:37:41 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/05 11:49:53 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_are_args_valid(char **av)
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

int	ft_setup_struct(t_data *data, char **av)
{
	data->n_of_philos = ft_atoi(av[1]);
	if (data->n_of_philos > 200 || data->n_of_philos == 0)
		return (1);
	data->die_ms = ft_atoi(av[2]);
	data->eat_ms = ft_atoi(av[3]);
	data->sleep_ms = ft_atoi(av[4]);
	if (av[5])
		data->total_meals = ft_atoi(av[5]);
	else
		data->total_meals = 0;
	data->philo = (t_philo *)ft_calloc(data->n_of_philos, sizeof(t_philo));
	if (!data->philo)
		return (1);
	return (0);
}

static int	ft_calloc_mutexes(t_data *data, int n_of_philos)
{
	int	i;

	i = -1;
	while (++i < n_of_philos)
	{
		data->philo[i].r_fork_lock = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->philo[i].r_fork_lock)
			return (1);
		data->philo[i].l_fork_lock = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->philo[i].l_fork_lock)
			return (1);
		data->philo[i].write_lock = &data->write_lock;
		data->philo[i].dead_lock = &data->dead_lock;
		data->philo[i].meal_lock = &data->meal_lock;
	}
	return (0);
}

int	ft_setup_mutex(t_data *data, int n_of_philos)
{
	int	i;

	if (ft_calloc_mutexes(data, n_of_philos))
		return (1);
	i = -1;
	while (++i < n_of_philos)
	{
		if (pthread_mutex_init(data->philo[i].r_fork_lock, NULL))
			return (1);
		if (pthread_mutex_init(data->philo[i].l_fork_lock, NULL))
			return (1);
		if (pthread_mutex_init(&data->write_lock, NULL))
			return (1);
		if (pthread_mutex_init(&data->dead_lock, NULL))
			return (1);
		if (pthread_mutex_init(&data->meal_lock, NULL))
			return (1);
	}
	return (0);
}
