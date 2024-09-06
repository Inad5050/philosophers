/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:29 by dani              #+#    #+#             */
/*   Updated: 2024/09/06 18:13:07 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//check if threads should stop
void	*checker(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	while (p->death == false && p->max_meals == false)
	{
		check_death(phi);
		if (p->number_of_times_each_philosopher_must_eat)
			check_max_meals(phi);
	}
	
	printf("CHECKER ended index %i\n", phi->index);
	
	return(NULL);
}

//check if a philosopher has died
void	check_death(t_phisolopher *phi)
{
	t_philo			*p;

	p = phi->philo;
	
	long  time;
	
	pthread_mutex_lock(&(phi->checker_mutex));

	time = get_time(p);
	
	if ((time - phi->last_meal) >= p->time_to_die)
	{
		printf("DEAD get_time - phi->last_meal >= p->time_to_die %lu %lu %lu\n", time, phi->last_meal, p->time_to_die);
		
		/* pthread_mutex_lock(&(phi->checker_mutex)); */
		pthread_mutex_lock(&(p->write_mutex));
		p->death = true;
		printf("%lu %i has died\n", get_time(p), phi->index);
		pthread_mutex_unlock(&(p->write_mutex));
		/* pthread_mutex_unlock(&(phi->checker_mutex)); */
	}
	pthread_mutex_unlock(&(phi->checker_mutex));
}
	
//check if all philosophers are full (if argc = 6)
void	check_max_meals(t_phisolopher *phi)
{
	int	i;
	t_philo			*p;

	p = phi->philo;
	i = 0;
	while (i < p->number_of_philosophers)
	{
		if (p->phi[i].times_eaten < p->number_of_times_each_philosopher_must_eat)
			break;
		i++;
	}
	if (i == p->number_of_philosophers - 1)
	{
		pthread_mutex_lock(&(phi->checker_mutex));
		p->max_meals = true;
		pthread_mutex_unlock(&(phi->checker_mutex));
		pthread_mutex_lock(&(p->write_mutex));
		printf("%lu %s\n", get_time(p),	"all philosophers are full");
		pthread_mutex_unlock(&(p->write_mutex));
	}
}
