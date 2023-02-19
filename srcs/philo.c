/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/02/20 02:07:28 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		if (table->philo[i].status == 1)
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (check_status(philo->table))
	{
		if (take_fork(philo))
			break ;
		if (eating(philo))
			break ;
	}
	return (NULL);
}

void	run_thread(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->num_of_philo)
	{
		table->philo[i].table = table;
		pthread_create(&table->philo[i].thread, NULL, &routine,
			&table->philo[i]);
	}
}

void	join_thread(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		pthread_join(table->philo[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_table		*table;

	if (check_arg(ac, av))
		exit(0);
	table = init_table(ac, av);
	run_thread(table);
	while (check_status(table))
		usleep(1);
	join_thread(table);
	philo_free(table);
	// system("leaks philo");
}
