/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/02/12 15:04:53 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		take_fork(philo);
		eating(philo);
		printf("%ld %d is sleeping\n", current_time(philo->table), philo->id);
		smart_usleep(philo, philo->table->time_to_sleep);
		printf("%ld %d is thinking\n", current_time(philo->table), philo->id);
		while (philo->left_fork->usage)
			smart_usleep(philo, 1);
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
}
