/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:28:56 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/13 17:08:15 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_debug(t_data *data)
{
	printf("die_ms: %ld\n", data->philo[0].die_ms);
	printf("eat_ms: %ld\n", data->philo[0].eat_ms);
	printf("sleep_ms: %ld\n", data->philo[0].sleep_ms);
	printf("total_meals: %d\n", data->philo[0].n_of_meals);
}

static int	ft_are_args_valid(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (printf("Error: incorrect number of arguments\n"));
	if (ft_are_args_valid(av))
		return (printf("Error: invalid argument(s)\n"));
	ft_philosophers(&data, av);
	ft_annihilation(data);
}
