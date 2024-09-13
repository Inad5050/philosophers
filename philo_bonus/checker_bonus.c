/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:29 by dani              #+#    #+#             */
/*   Updated: 2024/09/13 17:03:09 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*checker_routine(void *phi_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)phi_struct;
	p = phi->philo;
	while (check_end_condition(phi))
	{
		check_death(phi);
		if (p->number_of_times_each_philosopher_must_eat)
			check_max_meals(phi);
		if (check_end_condition(phi))
			ph_usleep(5, p);
	}
	return (phi_struct);
}

void	check_death(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	sem_wait(phi->eat_sem);
	if ((get_time(p) - phi->last_meal) >= p->time_to_die)
	{
		sem_wait(phi->end_sem);
		phi->end_condition = true;
		sem_post(phi->end_sem);
		ph_print("died", phi);
	}
	sem_post(phi->eat_sem);
}

void	check_max_meals(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	sem_wait(phi->eat_sem);
	if (phi->times_eaten == p->number_of_times_each_philosopher_must_eat)
	{
		sem_wait(phi->end_sem);
		phi->end_condition = true;
		sem_post(phi->end_sem);
	}
	sem_post(phi->eat_sem);
}

int	check_end_condition(t_phisolopher *phi)
{
	sem_wait(phi->end_sem);
	if (phi->end_condition == true)
	{
		sem_post(phi->end_sem);
		return (0);
	}
	sem_post(phi->end_sem);
	return (1);
}
