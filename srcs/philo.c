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

void	smart_usleep(t_philo *philo, int num)
{
	int	time;

	time = current_time(philo->table);
	while (current_time(philo->table) < time + num)
	{
		usleep(500);
		pthread_mutex_lock(&philo->table->mutex_death);
		if (current_time(philo->table)
			>= (philo->latest_meal + philo->table->time_to_die))
		{
			printf("%ld %d died\n", current_time(philo->table), philo->id);
			exit(0);
		}
		pthread_mutex_unlock(&philo->table->mutex_death);
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		smart_usleep(philo, 5);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->usage = philo->id;
	printf("%ld %d has taken a fork\n",
		current_time(philo->table), philo->id);
	if (philo->table->num_of_philo == 1)
	{
		while (1)
			smart_usleep(philo, 1);
	}
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->usage = philo->id;
	printf("%ld %d has taken a fork\n",
		current_time(philo->table), philo->id);
}

void	eating(t_philo *philo)
{
	philo->status = EATING;
	printf("%ld %d is eating\n", current_time(philo->table), philo->id);
	pthread_mutex_lock(&philo->mutex_latest_meal);
	philo->latest_meal = current_time(philo->table);
	pthread_mutex_unlock(&philo->mutex_latest_meal);
	pthread_mutex_lock(&philo->mutex_eat_count);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->mutex_eat_count);
	smart_usleep(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->left_fork->usage = 0;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->right_fork->usage = 0;
}

void	sleeping2thinking(t_philo *philo)
{
	philo->status = SLEEPING;
	printf("%ld %d is sleeping\n", current_time(philo->table), philo->id);
	smart_usleep(philo, philo->table->time_to_sleep);
	philo->status = THINKING;
	printf("%ld %d is thinking\n", current_time(philo->table), philo->id);
	if (philo->left_fork->usage)
	{
		while (1)
		{
			if (!philo->left_fork->usage)
				break ;
			smart_usleep(philo, 1);
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		take_fork(philo);
		eating(philo);
		sleeping2thinking(philo);
		int i;
		i = -1;
		while (++i < philo->table->num_of_philo)
		{
			printf("%d %d %d\n", philo[i].id, philo[i].eat_count, philo->table->times_eaten);
		}
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
