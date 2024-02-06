/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/06 16:32:37 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
int x = 0;

static void	*ft_routine(void *arg)
{
	t_philo *philo;

	philo = arg;

	// while (*philo->dead == false)
	// {
	// 	if (philo->meals_eaten >= philo->n_of_meals || philo->last_meal >= philo->die_ms)
	// 		*philo->dead = true;
		
		
	// }
	// printf("philo %d has\n\t-> r_fork %p\n\t-> l_fork %p\n", philo->id, philo->r_fork, philo->l_fork);
	// for (int i = 0; i < 1000000; i++){
	// 	pthread_mutex_lock(philo->write_lock);
	// 	x++;
	// 	pthread_mutex_unlock(philo->write_lock);
	// }
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
