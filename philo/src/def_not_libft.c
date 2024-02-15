/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_not_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:45:22 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/15 13:46:21 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_printf_alive(t_philo *philo, char code)
{
	pthread_mutex_lock(philo->dead_lock);
	pthread_mutex_lock(philo->write_lock);
	if (*philo->dead == false)
	{
		if (code == 'f')
			printf(FORK_MSG, get_current_time() - (philo)->start_ms, philo->id);
		if (code == 'e')
			printf(EAT_MSG, get_current_time() - (philo)->start_ms, philo->id);
		if (code == 's')
			printf(SLP_MSG, get_current_time() - (philo)->start_ms, philo->id);
		if (code == 't')
			printf(THNK_MSG, get_current_time() - (philo)->start_ms, philo->id);
	}
	if (code == 'd')
		printf(DEAD_MSG, get_current_time() - (philo)->start_ms, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->dead_lock);
}

void	ft_wait(t_philo *philo, size_t start, size_t ms)
{
	size_t	end;
	size_t	duration;

	end = get_current_time() - (philo)->start_ms;
	duration = end - start;
	while (duration < ms)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead == true)
		{
			pthread_mutex_unlock(philo->dead_lock);
			return ;
		}
		pthread_mutex_unlock(philo->dead_lock);
		ft_usleep(1);
		end = get_current_time() - (philo)->start_ms;
		duration = end - start;
		if (duration > philo->die_ms && *philo->dead == false)
		{
			*philo->dead = true;
			return ;
		}
	}
	return ;
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write (STDERR_FILENO, "gettimeofday() error\n", sizeof(char) * 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

bool	ft_is_meal_done(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_of_philos)
	{
		if (data->philo[i].meals_eaten < data->philo[i].n_of_meals)
			return (false);
	}
	return (true);
}
