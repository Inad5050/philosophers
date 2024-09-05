/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/06 01:40:41 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//initialize threads & end them
void	start_threads(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{		
		if (pthread_create(&(p->phi[i].th), NULL, &routine, &(p->phi[i])))
			ph_error("Failed to create thread", p);		
		usleep(1);		
		i++;
	}
	i = 0;
	while (i < p->number_of_philosophers)
	{			
		if (pthread_join(p->phi[i].th, NULL))
			ph_error("Failed to join thread", p);
		
		printf("JOINED %i\n", p->phi[i].index);
		
		i++;
	}
}

//make philosphers take the forks, eat, sleep and think
void	*routine(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	if (pthread_create(&(phi->th_checker), NULL, &checker, phi))
		ph_error("Failed to create thread", p);
	while (p->death == false && p->max_meals == false)
	{
		forks(phi, LOCK);
		philo_eat(phi);
		forks(phi, UNLOCK);
		ph_print("is sleeping", phi->index, p);
		usleep(p->time_to_sleep);
		ph_print("is thinking", phi->index, p);
	}
	if (pthread_join(phi->th_checker, NULL))
		ph_error("Failed to join thread", p);
	
	printf("ROUTINE ended index = %i\n", phi->index);
	
	return (NULL);
}

//philosophers take the forks
void	forks(t_phisolopher *phi, int i)
{
	t_philo	*p;

	p = phi->philo;
	if (i == LOCK)
	{
		pthread_mutex_lock(&(p->forks[phi->index]));
		ph_print("has taken a fork", phi->index, p);
		if (phi->index != p->number_of_philosophers - 1)
			pthread_mutex_lock(&(p->forks[phi->index + 1]));
		else
			pthread_mutex_lock(&(p->forks[0]));
		ph_print("has taken a fork", phi->index, p);
	}
	if (i == UNLOCK)
	{
		pthread_mutex_unlock(&(p->forks[phi->index]));
		if (phi->index != p->number_of_philosophers - 1)
			pthread_mutex_unlock(&(p->forks[phi->index + 1]));
		else
			pthread_mutex_unlock(&(p->forks[0]));
	}
}

void	philo_eat(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	pthread_mutex_lock(&(phi->checker_mutex));
	phi->last_meal = get_time(phi->philo);		
	phi->times_eaten++;
	pthread_mutex_unlock(&(phi->checker_mutex));
	ph_print("is eating", phi->index, phi->philo);
	usleep(p->time_to_eat);
}
