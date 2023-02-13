/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:51:42 by mliew             #+#    #+#             */
/*   Updated: 2023/01/10 15:33:14 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_error(t_table *table)
{
	(void)table;
	// free(table->fork);
	// free(table->philo);
	// free(table);
	system("leaks philo");
	exit(0);
}

long	ft_atol(const char *str)
{
	int		i;
	int		neg;
	long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = (nbr * 10) + (str[i++] - '0');
	return (nbr * neg);
}

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i] >= '0' && str[i++] <= '9')
			return (1);
	return (0);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Only 4 or 5 arguments.\n"));
	while (++i < ac)
	{
		if (ft_atol(av[i]) < 1 || ft_atol(av[i]) > 2147483647)
			return (printf("Numbers cannot be more than max int.\n"));
		if (!ft_strisdigit(av[i]))
			return (printf("Numbers cannot be less than 0.\n"));
	}
	return (0);
}
