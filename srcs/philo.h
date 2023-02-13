/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:37:40 by mliew             #+#    #+#             */
/*   Updated: 2023/02/09 14:19:30 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define THINKING 0
# define EATING 1
# define SLEEPING 2

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				usage;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				eat_count;
	int				latest_meal;
	int				status;
	pthread_mutex_t	mutex_latest_meal;
	pthread_mutex_t	mutex_eat_count;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_eaten;
	long			start_time;
	t_philo			*philo;
	t_fork			*fork;
	pthread_mutex_t	mutex_message;
	pthread_mutex_t	mutex_death;
}	t_table;

// check
void	free_error(t_table *table);
int		check_arg(int ac, char **av);
long	ft_atol(const char *str);
int		ft_strisdigit(char *str);

// init
void	init_fork(t_table *table);
void	init_philo(t_table *table);
t_table	*init_table(int ac, char **av);

// utils
long	get_time(void);
long	current_time(t_table *table);

#endif