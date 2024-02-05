/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/05 16:08:19 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
int x = 0;

static void	*ft_routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (true)
	{
		*philo->dead = true;
		printf("philo %d is doing something\n", philo->id);
		if (*philo->dead == true)
			return (0);
	}
	return (0);
}

static int	ft_threads(t_data *data, int n_of_philos)
{
	int	i;

	i = -1;
	while (++i < n_of_philos)
		if (pthread_create(&data->philo[i].thread, NULL, &ft_routine, &data->philo[i]))
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
	if (ft_setup_mutex(*data, (*data)->n_of_philos))
		return (printf("Error: unable to initialize mutexes\n"));
	if (ft_threads(*data, (*data)->n_of_philos))
		return (printf("Error: unable to create threads\n"));
	return (0);
}
