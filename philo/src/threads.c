/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/14 15:49:45 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_threads(t_data *data, int n_of_philos)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < n_of_philos)
		if (pthread_create(&data->philo[i].thread, NULL,
				&ft_philos, &data->philo[i]))
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

int	ft_initialization(t_data **data, char **av)
{
	pthread_mutex_t	*forks;
	int				i;

	*data = (t_data *)malloc(sizeof(t_data));
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atol(av[2]));
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
