/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:39 by mliew             #+#    #+#             */
/*   Updated: 2023/02/06 13:52:07 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	usleep(philo->id * 100);
	printf("%ld %d is thinking\n", current_time(philo->table), philo->id);
	pthread_mutex_lock(&philo->left_fork->mutex);
	printf("%ld %d has taken a fork\n", current_time(philo->table), philo->id);
	pthread_mutex_lock(&philo->right_fork->mutex);
	printf("%ld %d has taken a fork\n", current_time(philo->table), philo->id);
	philo->status = EATING;
}

void	eating(t_philo *philo)
{
	if (current_time(philo->table)
		> (philo->latest_meal + philo->table->time_to_die))
	{
		printf("%ld %d died\n", current_time(philo->table), philo->id);
		exit(0);
	}
	printf("%ld %d is eating\n", current_time(philo->table), philo->id);
	usleep(philo->table->time_to_eat * 1000);
	philo->latest_meal = current_time(philo->table);
	philo->eat_count += 1;
	philo->status = SLEEPING;
}

void	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", current_time(philo->table), philo->id);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	usleep(philo->table->time_to_sleep * 1000);
	philo->status = THINKING;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->status == THINKING)
			take_fork(philo);
		if (philo->status == EATING)
			eating(philo);
		if (philo->status == SLEEPING)
			sleeping(philo);
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
