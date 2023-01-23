/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/01/23 15:27:12 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	if (philo->left_fork->usage == 0)
	{
		philo->left_fork->usage = philo->id;
		printf("%ld %d has taken a fork\n", current_time(philo->table), philo->id);
	}
	if (philo->right_fork->usage == 0 && philo->left_fork->usage == philo->id)
	{
		philo->right_fork->usage = philo->id;
		printf("%ld %d has taken a fork\n", current_time(philo->table), philo->id);
	}
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	eating(t_philo *philo)
{
	if (philo->left_fork->usage == philo->id && philo->right_fork->usage == philo->id)
	{
		philo->latest_meal = current_time(philo->table);
		philo->eat_count += 1;
		printf("%ld %d is eating\n", current_time(philo->table), philo->id);
		philo->left_fork->usage = 0;
		philo->right_fork->usage = 0;
	}
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		while (philo->table->start_time + 1000 > philo->table->start_time)
			usleep(500);
	take_fork(philo);
	eating(philo);
	// printf("%ld Philo No.%d Left:%p Right:%p\n",
	// 	current_time(philo->table) ,philo->id, philo->left_fork, philo->right_fork);
	// printf("%ld Philo No.%d Eat_Count:%d Latest_Meal:%d\n",
	// 	current_time(philo->table) ,philo->id, philo->eat_count, philo->latest_meal);
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
