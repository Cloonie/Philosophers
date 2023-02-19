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

void	printing(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->table->mutex_print);
	if (check_status(philo->table))
		printf("%ld %d %s\n", current_time(philo->table), philo->id, state);
	pthread_mutex_unlock(&philo->table->mutex_print);
}

int	check_eat_count(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_of_philo && philo->table->times_eaten != 0
		&& philo->table->philo[i].eat_count == philo->table->times_eaten)
	{
		if (i == philo->table->num_of_philo - 1)
			return (1);
		i++;
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
		pthread_mutex_lock(&philo->table->mutex_death);
		if (current_time(philo->table)
			>= (philo->latest_meal + philo->table->time_to_die))
		{
			printing(philo, "died");
			philo->status = 1;
		}
		if (check_eat_count(philo))
			philo->status = 1;
		pthread_mutex_unlock(&philo->table->mutex_death);
	}
	if (philo->status == 1)
		return (1);
	return (0);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (smart_usleep(philo, 1))
			return (1);
		printing(philo, "is thinking");
	}
	if (philo->left_fork)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->usage = philo->id;
		printing(philo, "has taken a fork");
	}
	if (philo->right_fork)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->usage = philo->id;
		printing(philo, "has taken a fork");
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->left_fork->usage == philo->id
		&& philo->right_fork != NULL)
	{
		pthread_mutex_lock(&philo->mutex_latest_meal);
		philo->latest_meal = current_time(philo->table);
		pthread_mutex_unlock(&philo->mutex_latest_meal);

		printing(philo, "is eating");
		if (smart_usleep(philo, philo->table->time_to_eat))
			return (1);

		pthread_mutex_lock(&philo->mutex_eat_count);
		philo->eat_count += 1;
		pthread_mutex_unlock(&philo->mutex_eat_count);
		if (smart_usleep(philo, 1))
			return (1);

		pthread_mutex_unlock(&philo->left_fork->mutex);
		philo->left_fork->usage = 0;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		philo->right_fork->usage = 0;

		if (check_status(philo->table))
		{
			printing(philo, "is sleeping");
			if (smart_usleep(philo, philo->table->time_to_sleep))
				return (1);

			printing(philo, "is thinking");
		}
	}
	while (philo->left_fork->usage != 0)
		if (smart_usleep(philo, 1))
			return (1);
	return (0);
}
