/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/01/05 23:28:17 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *routine()
// {
// 	printf("routine works\n");
// 	return (0);
// }

void	init_fork(t_table *table)
{
	int	i;

	table->fork = malloc(table->num_of_philo * (sizeof(t_fork)));
	if (table->fork == NULL)
		error();
	i = -1;
	while (++i < table->num_of_philo)
		pthread_mutex_init(&table->fork[i].mutex, NULL);
}

void	init_philo(t_table *table)
{
	int	i;

	table->philo = malloc(table->num_of_philo * sizeof(t_philo));
	if (table->philo == NULL)
		error();
	i = -1;
	while (++i < table->num_of_philo)
	{
		table->philo[i].number = i + 1;
		table->philo[i].left_fork = table->fork[i];
		table->philo[i].right_fork = 0;
		table->philo[i].eat_count = 0;
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
	return (table);
}

int	main(int ac, char **av)
{
	t_table		*table;

	if (check_arg(ac, av))
		error();
	table = init_table(ac, av);

	pthread_mutex_t	mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	pthread_mutex_destroy(&mutex);

	// pthread_t	t[2];
	// int	i;
	// i = -1;
	// while (++i < 3)
	// {
	// 	pthread_create(&t[i], NULL, &routine, NULL);
	// 	pthread_join(t[i], NULL);
	// }
}
