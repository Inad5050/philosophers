/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:36:42 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 19:18:18 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_philo *p)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ph_error("Couldn't get_time", p), 0);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

void	ph_print(char *str, int i, t_philo *p)
{
	pthread_mutex_lock(&(p->write_mutex));
	if (!ft_strncmp(str, "died", 5))
		printf("%lu %i %s\n", get_time(p) - p->initial_time, i + 1, str);
	if (check_end_condition(&(p->phi[i])))
		printf("%lu %i %s\n", get_time(p) - p->initial_time, i + 1, str);
	pthread_mutex_unlock(&(p->write_mutex));
}

void	ph_usleep(long time, t_philo *p)
{
	long	start;

	start = get_time(p);
	while ((get_time(p) - start) < time)
		usleep(time / 10);
}
