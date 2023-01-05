/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:37:40 by mliew             #+#    #+#             */
/*   Updated: 2023/01/05 22:49:12 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	int			number;
	int			eat_count;
}	t_philo;

typedef struct s_table
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_eaten;
	t_philo	*philo;
	t_fork	*fork;
}	t_table;

void	error(void);
int		check_arg(int ac, char **av);
long	ft_atol(const char *str);
int		ft_strisdigit(char *str);

#endif