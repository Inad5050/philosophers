/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:29 by dani              #+#    #+#             */
/*   Updated: 2024/09/05 03:01:09 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//check if threads should stop
void	stop_condition(t_philo *p)
{
	while (p->death == false && p->max_meals == false)
	{
		pthread_mutex_lock(&(p->death_mutex));
		check_death(p);
		check_max_meals(p);
		pthread_mutex_unlock(&(p->death_mutex));
	}
}

//check if a philosopher has died
void	check_death(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		if (p->phi[i].last_meal - get_time(p) >= p->time_to_die)
		{
			pthread_mutex_lock(&(p->write_mutex));
			p->death = true;
			printf("%lu %i died\n", get_time(p), i);
			pthread_mutex_unlock(&(p->write_mutex));
			break;
		}
		i++;
	}
}
	
//check if all philosophers are full (if argc = 6)
void	check_max_meals(t_philo *p)
{
	int	i;

	i = 0;
	while (p->number_of_times_each_philosopher_must_eat && \
	p->phi[i].times_eaten >= p->number_of_times_each_philosopher_must_eat)
		i++;
	if (i == p->number_of_philosophers - 1)
	{
		p->max_meals = true;
		pthread_mutex_lock(&(p->write_mutex));
		printf("%lu %s\n", get_time(p) - p->initial_time, \
		"All philosophers are full");
		pthread_mutex_unlock(&(p->write_mutex));
	}
}
