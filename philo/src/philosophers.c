/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/31 14:08:20 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
int x = 0;

static void	*ft_routine(void *arg)
{
	t_data	*data;

	data = arg;
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(data->philo[0].r_fork_lock); //  <---- figure this one out
		x++;
		pthread_mutex_unlock(data->philo[0].r_fork_lock);
	}
	return (0);
}

static int	ft_threads(t_data *data, int n_of_philos)
{
	int	i;

	i = -1;
	while (++i < n_of_philos)
		if (pthread_create(&data->philo[i].thread, NULL, &ft_routine, &data))
			return (1);
	i = -1;
	while (++i < n_of_philos)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	printf("x -> %d\n", x);
	return (0);
}

int	ft_philosophers(t_data **data, char **av)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return (printf("Error: unable to malloc (data)\n"));
	if (ft_setup_struct(*data, av))
		return (printf("Error: unable to setup data\n"));
	if (ft_setup_mutex(*data, ft_atoi(av[1])))
		return (printf("Error: unable to initialize mutexes\n"));
	if (ft_threads(*data, ft_atoi(av[1])))
		return (printf("Error: unable to create threads\n"));
	return (0);
}
