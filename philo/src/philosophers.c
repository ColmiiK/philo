/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/12 13:48:29 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void ft_printf_alive(t_philo *philo, char code)
{
	if (*philo->dead == false)
	{
		if (code == 'f')
			printf("%zu %d has taken a fork\n", TIME, philo->id);
		if (code == 'e')
			printf("%zu %d is eating\n", TIME, philo->id);
	}
}

static void ft_wait(t_philo *philo,size_t start, size_t ms)
{
	size_t end;
	size_t duration;

	end = TIME;
	duration = end - start;
	while (duration < ms)
	{
		ft_usleep(1);
		end = TIME;
		duration = end - start;
		if (duration > philo->die_ms && *philo->dead == false)
		{
			*philo->dead = true;
			return ;
		}
	}
	return ;
}

static void ft_take_forks(t_philo *philo)
{
	philo->time = TIME;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_printf_alive(philo, 'f');
		if (philo->r_fork == philo->l_fork)
		{
			*philo->dead = true;
			printf("%zu %d died\n", TIME, philo->id);
			return ;
		}
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ft_printf_alive(philo, 'f');
		pthread_mutex_lock(philo->r_fork);
	}
	philo->time = TIME - philo->time;
	if (philo->time > philo->die_ms)
		*philo->dead = true;
}

static void ft_eat(t_philo *philo)
{
	size_t meal_start;

	meal_start = TIME;
	ft_printf_alive(philo, 'f');
	ft_printf_alive(philo, 'e');
	ft_wait(philo, meal_start, philo->eat_ms);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->time = (TIME - meal_start) + philo->time;
	if (philo->time > philo->die_ms)
		*philo->dead = true;
}

static void	*ft_routine(void *arg)
{
	t_philo *philo;
	size_t sleep_start;

	philo = (t_philo *)arg;
	while (*philo->dead == false)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		if (*philo->dead == true)
		{
			ft_printf_alive(philo, 'd'); // <---
			return (NULL);
		}
		sleep_start = TIME;
		printf("%zu %d is sleeping\n", TIME, philo->id);
		ft_wait(philo, sleep_start, philo->sleep_ms);
		if (*philo->dead == true)
			return (NULL);
		printf("%zu %d is thinking\n", TIME, philo->id);
	}
	return (NULL);
	
}

static void *ft_monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while (true)
	{
		i = -1;
		while (++i < data->n_of_philos)
		{
			if (data->dead == true)
				return (NULL);
			if (data->philo[i].n_of_meals == -1)
				;
			else if (data->philo[i].meals_eaten >= data->philo[i].n_of_meals)
			{
				data->dead = true;
				return (NULL);
			}
		}
	}
	return (NULL);
}

static int	ft_threads(t_data *data, int n_of_philos)
{
	int	i;
	pthread_t monitor;

	i = -1;
	while (++i < n_of_philos)
		if (pthread_create(&data->philo[i].thread, NULL, &ft_routine, &data->philo[i]))
			{
				data->dead = true;
				return (1);
			}
	if (pthread_create(&monitor, NULL, &ft_monitor, data))
	{
		data->dead = true;
		return (1);
	}
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
