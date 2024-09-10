/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:29 by dani              #+#    #+#             */
/*   Updated: 2024/09/11 01:02:56 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check if threads should stop
void	*checker(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	while (p->death == false && p->max_meals < p->number_of_philosophers)
	{
		pthread_mutex_lock(&(phi->checker_mutex));
		check_death(phi);
		if (p->number_of_times_each_philosopher_must_eat)
			check_max_meals(phi);
		pthread_mutex_unlock(&(phi->checker_mutex));
		if (p->death == false && p->max_meals < p->number_of_philosophers)
			usleep((8 * (long)1000));
	}
	return (NULL);
}

//check if a philosopher has died
void	check_death(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	if ((get_time(p) - phi->last_meal) > p->time_to_die)
	{
		pthread_mutex_lock(&(p->write_mutex));
		if (p->death == false)
			printf("%lu %i has died\n", get_time(p) - \
			p->initial_time, phi->index);
		p->death = true;
		pthread_mutex_unlock(&(p->write_mutex));
	}
}

//check if all philosophers are full
void	check_max_meals(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	if (phi->times_eaten == p->number_of_times_each_philosopher_must_eat)
	{
		p->max_meals++;
		if (p->max_meals == p->number_of_philosophers)
		{
			pthread_mutex_lock(&(p->write_mutex));
			printf("%lu all philosophers are full\n", \
				get_time(p) - p->initial_time);
			pthread_mutex_unlock(&(p->write_mutex));
		}
	}
}
