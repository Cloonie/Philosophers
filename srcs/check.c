/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:51:42 by mliew             #+#    #+#             */
/*   Updated: 2023/02/26 07:07:40 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		pthread_mutex_destroy(&table->fork[i].mutex);
	i = -1;
	while (++i < table->num_of_philo)
	{
		pthread_mutex_destroy(&table->philo[i].mutex_latest_meal);
	}
	free(table->fork);
	free(table->philo);
	pthread_mutex_destroy(&table->mutex_eat_count);
	pthread_mutex_destroy(&table->mutex_print);
	pthread_mutex_destroy(&table->mutex_death);
	free(table);
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
		return (printf("Error, please input only 4 or 5 arguments.\n"));
	while (++i < ac)
	{
		if (ft_atol(av[i]) < 1 || ft_atol(av[i]) > 2147483647)
			return (printf("Error, please input numbers 1 - 2147483647.\n"));
		if (!ft_strisdigit(av[i]))
			return (printf("Error, please input numbers only.\n"));
	}
	return (0);
}
