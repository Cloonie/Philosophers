/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/01/11 18:32:24 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_table	*table;

	table = arg;
	usleep(500);
	printf("start_time:%ld\n", table->start_time);
	printf("get_time:%ld\n", get_time());
	printf("current_time:%ld\n\n", current_time(table));
	if (current_time(table) > table->time_to_die)
		free_error(table);
	return (NULL);
}

void	run_thread(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->num_of_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, &routine, table);
		pthread_join(table->philo[i].thread, NULL);
	}
}

int	main(int ac, char **av)
{
	t_table		*table;

	if (check_arg(ac, av))
		exit(0);
	table = init_table(ac, av);
	run_thread(table);
}
