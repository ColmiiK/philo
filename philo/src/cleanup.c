/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:49:31 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/31 12:49:34 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_annihilation(t_data *data)
{
	// pthread_mutex_destroy(data->philo->fork_l);
	// pthread_mutex_destroy(data->philo->fork_r);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}
