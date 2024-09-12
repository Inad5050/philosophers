/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:29 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 03:57:21 by dani             ###   ########.fr       */
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
	while (p->death == false && p->full == false)
	{
		pthread_mutex_lock(&(phi->checker_mutex));
		check_death(phi);
		if (p->number_of_times_each_philosopher_must_eat)
			check_phi_max_meals(phi);
		pthread_mutex_unlock(&(phi->checker_mutex));
		if (p->death == false && phi->max_meals == false)
			ft_usleep(5, p);
	}

	printf("CHECKER %i termina\n", phi->index);
	
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
			p->initial_time, phi->index + 1);
		p->death = true;
		pthread_mutex_unlock(&(p->write_mutex));
	}
}

//check if all philosophers are full
void	check_phi_max_meals(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	pthread_mutex_lock(&(p->end_condition_mutex));
	if (phi->times_eaten == p->number_of_times_each_philosopher_must_eat)
		phi->max_meals = true;
	pthread_mutex_unlock(&(p->end_condition_mutex));
}
