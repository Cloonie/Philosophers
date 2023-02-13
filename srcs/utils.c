/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:29:39 by mliew             #+#    #+#             */
/*   Updated: 2023/01/03 17:29:39 by mliew            ###   ########.fr       */
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

void	check_eat_count(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_of_philo && philo->table->times_eaten)
	{
		while (philo->table->philo[i].eat_count == philo->table->times_eaten)
		{
			i++;
			if (i == philo->table->num_of_philo - 1)
				exit(0);
		}
		i = 0;
		break ;
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		smart_usleep(philo, 1);
		printf("%ld %d is thinking\n", current_time(philo->table), philo->id);
	}
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->usage = philo->id;
	printf("%ld %d has taken a fork\n",
		current_time(philo->table), philo->id);
	while (philo->table->num_of_philo == 1)
		smart_usleep(philo, 1);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->usage = philo->id;
	printf("%ld %d has taken a fork\n",
		current_time(philo->table), philo->id);
}

void	eating(t_philo *philo)
{
	printf("%ld %d is eating\n", current_time(philo->table), philo->id);
	pthread_mutex_lock(&philo->mutex_latest_meal);
	philo->latest_meal = current_time(philo->table);
	pthread_mutex_unlock(&philo->mutex_latest_meal);
	smart_usleep(philo, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->mutex_eat_count);
	philo->eat_count += 1;
	check_eat_count(philo);
	pthread_mutex_unlock(&philo->mutex_eat_count);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->left_fork->usage = 0;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->right_fork->usage = 0;
}
