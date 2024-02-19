/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:28:56 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/19 16:14:38 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("Error: incorrect number of arguments\n");
		return (1);
	}
	if (ft_are_args_valid(av))
	{
		printf("Error: invalid argument(s)\n");
		return (1);
	}
	ft_initialization(&data, av);
	ft_annihilation(data);
	return (0);
}
