/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:42:14 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/15 13:47:34 by alvega-g         ###   ########.fr       */
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
	pthread_mutex_lock(philo->meal_lock);
	philo->meal_duration = get_current_time() - (philo)->start_ms - philo->time;
	pthread_mutex_unlock(philo->meal_lock);
	ft_printf_alive(philo, 'e');
	ft_wait(philo, get_current_time() - (philo)->start_ms, philo->eat_ms);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*ft_philos(void *arg)
{
	t_philo	*philo;
	size_t	sleep_start;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(2);
	while (true)
	{
		if (ft_flag_check(philo))
			return (NULL);
		if (philo->n_of_meals != -1 && philo->meals_eaten >= philo->n_of_meals)
			return (NULL);
		ft_eat(philo);
		if (ft_flag_check(philo))
			return (NULL);
		sleep_start = get_current_time() - (philo)->start_ms;
		ft_printf_alive(philo, 's');
		ft_wait(philo, sleep_start, philo->sleep_ms);
		if (ft_flag_check(philo))
			return (NULL);
		ft_printf_alive(philo, 't');
	}
	return (NULL);
}

static int	ft_monitor_ifs(t_data *data, int i)
{
	if (data->philo[i].r_fork == data->philo[i].l_fork)
		data->dead = true;
	pthread_mutex_lock(&data->meal_lock);
	if (data->philo[i].meal_duration + data->philo[i].eat_ms
		> data->philo[i].die_ms)
		ft_flag_change(data);
	if (data->philo[i].n_of_meals == -1)
		;
	else if (ft_is_meal_done(data))
	{
		ft_flag_change(data);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_lock);
	if (data->dead == true)
	{
		ft_usleep(2);
		ft_printf_alive(&data->philo[i], 'd');
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->dead == false)
	{
		i = -1;
		while (++i < data->n_of_philos)
			if (ft_monitor_ifs(data, i))
				return (NULL);
	}
	return (NULL);
}
