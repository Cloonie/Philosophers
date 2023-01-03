/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/01/03 20:49:17 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hi(void);

void	error(void)
{
	printf("Error\n");
	exit(0);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("ac wrong\n"));
	if (++i < ac)
	{
		if (ft_isdigit(av[i]))
			return (printf("digit wrong\n"));
		if (ft_atoi(av[i]) < 1)
			return (printf("atoi wrong\n"));
	}
	return (0);
}
int	main(int ac, char **av)
{
	// int	number_of_philosophers;
	// int	time_to_die;
	// int	time_to_eat;
	// int	time_to_sleep;
	// int	num_philo_eat;

	if (check_arg(ac, av))
		error();
	// number_of_philosophers = atoi(av[1]);
	// time_to_die = atoi(av[2]);
	// time_to_eat = atoi(av[3]);
	// time_to_sleep = atoi(av[4]);
	// num_philo_eat = atoi(av[5]);
}
