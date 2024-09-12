/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:49:10 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/12 15:30:14 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_philo *p)
{
	int	i;

	if (pthread_create(&(p->checker_th), NULL, &checker_routine, &p) != 0)
		ph_error("Failed to create watcher thread", p);
	if (p->number_of_philosophers == 1)
	{
		if (pthread_create(&(p->phi[0].th), NULL, &one_philo, &(p->phi[0])))
			ph_error("Failed to create thread", p);
		return ;
	}
	i = -1;
	while (++i < p->number_of_philosophers)
	{
		if (pthread_create(&(p->phi[i].th), NULL, &philo_routine, &(p->phi[i])))
			ph_error("Failed to create thread", p);
		ph_usleep(1, p);
	}
	if (pthread_join(p->checker_th, NULL))
		ph_error("Failed to join thread", p);
	i = -1;
	while (++i < p->number_of_philosophers)
	{
		if (pthread_join(p->phi[i].th, NULL))
			ph_error("Failed to join thread", p);		
	}
}

void	*philo_routine(void *phi_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)phi_struct;
	p = phi->philo;
	phi->last_meal = get_time(p);
	while (check_end_condition(phi))
	{
		philo_eat(phi);
		ph_print("is sleeping", phi->index, p);
		ph_usleep(p->time_to_sleep, p);
		ph_print("is thinking", phi->index, p);
	}
	return (phi_struct);
}

void	philo_eat(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	forks(phi, LOCK);
	ph_print("is eating", phi->index, phi->philo);	
	phi->eating = true;
	pthread_mutex_lock(&(p->eat_mutex));
	phi->last_meal = get_time(phi->philo);
	phi->times_eaten++;
	pthread_mutex_unlock(&(p->eat_mutex));
	ph_usleep(p->time_to_eat, p);
	phi->eating = false;
	forks(phi, UNLOCK);
}

void	forks(t_phisolopher *phi, int i)
{
	t_philo	*p;
	int		second_fork;

	p = phi->philo;
	second_fork = (phi->index + 1) % p->number_of_philosophers;
	if (i == LOCK)
	{
		if (phi->index % 2 == 0)
			pthread_mutex_lock(&(p->forks[second_fork]));
		pthread_mutex_lock(&(p->forks[phi->index]));
		ph_print("has taken a fork", phi->index, p);
		if (phi->index % 2 != 0)
			pthread_mutex_lock(&(p->forks[second_fork]));
		ph_print("has taken a fork", phi->index, p);
	}
	if (i == UNLOCK)
	{
		pthread_mutex_unlock(&(p->forks[phi->index]));
		pthread_mutex_unlock(&(p->forks[second_fork]));
	}
}

int	check_end_condition(t_phisolopher *phi)
{
	t_philo	*p;
	
	p = phi->philo;
	pthread_mutex_lock(&(p->end_condition_mutex));
	if (phi->end_condition == true)
	{
		pthread_mutex_unlock(&(p->end_condition_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(p->end_condition_mutex));
	return (1);
}
