/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:59 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/15 13:48:06 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*memory;

	memory = (void *)malloc(n * size);
	if (!memory)
		return (0);
	memset(memory, 0, n * size);
	return (memory);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}

long	ft_atol(const char *str)
{
	long	i;
	long	x;
	int		is_negative;

	i = 0;
	x = 0;
	is_negative = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = (x * 10) + (str[i] - '0');
		i++;
	}
	return (x * is_negative);
}

int	ft_flag_check(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	ft_flag_change(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = true;
	pthread_mutex_unlock(&data->dead_lock);
}
