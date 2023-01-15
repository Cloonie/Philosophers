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

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// printf("sec:%ld\n", tv.tv_sec);
	// printf("usec:%ld\n", tv.tv_usec);
	// printf("since 1/1/1970:%ld\n", (tv.tv_sec * 1000000) + tv.tv_usec);

	// struct tm *info;
	// info = localtime(&tv.tv_sec);
	// printf("%s", asctime(info));

	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	current_time(t_table *table)
{
	return (get_time() - table->start_time);
}
