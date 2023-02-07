/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:29:17 by mliew             #+#    #+#             */
/*   Updated: 2023/01/11 16:29:17 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_table *table)
{
	int	i;

	table->fork = malloc(table->num_of_philo * (sizeof(t_fork)));
	if (table->fork == NULL)
		free_error(table);
	i = -1;
	while (++i < table->num_of_philo)
	{
		pthread_mutex_init(&table->fork[i].mutex, NULL);
		table->fork[i].usage = 0;
	}
}

void	init_philo(t_table *table)
{
	int	i;

	table->philo = malloc(table->num_of_philo * sizeof(t_philo));
	if (table->philo == NULL)
		free_error(table);
	i = -1;
	while (++i < table->num_of_philo)
	{
		pthread_mutex_init(&table->mutex, NULL);
		table->philo[i].id = i + 1;
		table->philo[i].eat_count = 0;
		table->philo[i].latest_meal = 0;
		table->philo[i].status = 0;
		table->philo[i].left_fork = &table->fork[i];
		if (i + 1 != table->num_of_philo)
			table->philo[i].right_fork = &table->fork[i + 1];
		else if (table->num_of_philo != 1)
			table->philo[i].right_fork = &table->fork[0];
		else
			table->philo[i].right_fork = NULL;
	}
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->num_of_philo = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		table->times_eaten = atoi(av[5]);
	init_fork(table);
	init_philo(table);
	return (table);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	current_time(t_table *table)
{
	return (get_time() - table->start_time);
}
