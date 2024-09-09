/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:36:42 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 01:41:47 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(t_philo *p)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ph_error("Couldn't get_time", p), 0);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

void	ph_print(char *str, int i, t_philo *p)
{
	sem_wait(p->write_sem);
	if (p->death == false && p->max_meals == false)
		printf("%lu %i %s\n", get_time(p) - p->initial_time, i, str);
	sem_post(p->write_sem);
}

void	ft_usleep(long time, t_philo *p)
{
	long	start;

	start = get_time(p);
	while ((get_time(p) - start) < time)
		usleep(time / 10);
}
