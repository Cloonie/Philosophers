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

int	printing(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->table->mutex_print);
	if (check_status(philo->table) == 0)
	{
		pthread_mutex_unlock(&philo->table->mutex_print);
		return (1);
	}
	printf("%ld %d %s\n", current_time(philo->table), philo->id, state);
	pthread_mutex_unlock(&philo->table->mutex_print);
	return (0);
}

int	check_eat_count(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_of_philo && philo->table->times_eaten != 0)
	{
		if (i + 1 == philo->table->num_of_philo)
		{
			pthread_mutex_lock(&philo->table->mutex_death);
			philo->status = 1;
			pthread_mutex_unlock(&philo->table->mutex_death);
			return (1);
		}
		if (philo->table->philo[i].eat_count == philo->table->times_eaten)
			i++;
		else
			break ;
	}
	return (0);
}

int	smart_usleep(t_philo *philo, int num)
{
	long	time;

	time = current_time(philo->table);
	while (current_time(philo->table) < time + num)
	{
		usleep(500);
		if (current_time(philo->table)
			>= (philo->latest_meal + philo->table->time_to_die))
		{
			printing(philo, "died");
			pthread_mutex_lock(&philo->table->mutex_death);
			philo->status = 1;
			pthread_mutex_unlock(&philo->table->mutex_death);
			return (1);
		}
	}
	return (0);
}

int	take_fork(t_philo *philo, t_fork *fork)
{
	int	used;

	used = 0;
	if (fork == NULL)
		return (1);
	while (!used)
	{
		pthread_mutex_lock(&fork->mutex);
		if (fork->usage == 0)
		{
			fork->usage = philo->id;
			used = 1;
		}
		pthread_mutex_unlock(&fork->mutex);
		if (!used)
			smart_usleep(philo, 1);
	}
	if (printing(philo, "has taken a fork"))
		return (1);
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->left_fork->usage == philo->id
		&& philo->right_fork->usage == philo->id)
	{
		pthread_mutex_lock(&philo->mutex_latest_meal);
		philo->latest_meal = current_time(philo->table);
		pthread_mutex_unlock(&philo->mutex_latest_meal);
		if (printing(philo, "is eating"))
			return (1);
		smart_usleep(philo, philo->table->time_to_eat);
		pthread_mutex_lock(&philo->table->mutex_eat_count);
		philo->eat_count += 1;
		check_eat_count(philo);
		pthread_mutex_unlock(&philo->table->mutex_eat_count);
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->usage = 0;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->usage = 0;
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	return (0);
}
