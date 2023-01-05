/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:51:42 by mliew             #+#    #+#             */
/*   Updated: 2023/01/05 20:36:47 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (++i < ac)
	{
		if (ft_atol(av[i]) < 1 || ft_atol(av[i]) > 2147483647)
			return (printf("ft_atol wrong\n"));
		if (!ft_strisdigit(av[i]))
			return (printf("ft_isdigit wrong\n"));
	}
	return (0);
}
