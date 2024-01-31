/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:49:31 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/31 17:19:08 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_annihilation(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	i = -1;
	if (data->philo)
	{
		while (++i < data->n_of_philos)
		{
			pthread_mutex_destroy(data->philo[i].r_fork_lock);
			pthread_mutex_destroy(data->philo[i].l_fork_lock);
			free(data->philo[i].r_fork_lock);
			free(data->philo[i].l_fork_lock);
		}
		free(data->philo);
	}
	if (data)
		free(data);
}
