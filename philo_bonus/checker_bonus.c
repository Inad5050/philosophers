/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:29 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 00:58:02 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//check if threads should stop
void	*checker(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	while (p->death == false && p->max_meals == false)
	{
		sem_wait(phi->checker_sem);
		check_death(phi);
		if (p->number_of_times_each_philosopher_must_eat)
			check_max_meals(phi);
		sem_post(phi->checker_sem);
	}

	printf("CHECKER termina index = %i\n", phi->index);
	
	return (NULL);
}

//check if a philosopher has died
void	check_death(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	if ((get_time(p) - phi->last_meal) >= p->time_to_die)
	{
		sem_wait(p->write_sem);
		if (p->death == false)
			printf("%lu %i has died\n", get_time(p) - \
			p->initial_time, phi->index);
		p->death = true;
		sem_post(p->write_sem);
	}
}

//check if all philosophers are full
void	check_max_meals(t_phisolopher *phi)
{
	int		i;
	t_philo	*p;

	p = phi->philo;
	i = 0;
	while (i < p->number_of_philosophers)
	{
		if (p->phi[i].times_eaten < \
		p->number_of_times_each_philosopher_must_eat)
			break ;
		i++;
	}
	if (i == p->number_of_philosophers)
	{
		sem_wait(p->write_sem);
		if (p->max_meals == false)
			printf("%lu %s\n", get_time(p) - p->initial_time, \
			"all philosophers are full");
		p->max_meals = true;
		sem_post(p->write_sem);
	}
}
