/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/10 12:22:35 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//start the philosophers and wait for them to finish
void	start_threads(t_philo *p)
{
	int	i;

	if (p->number_of_philosophers == 1)
	{
		if (pthread_create(&(p->phi[0].th), NULL, &one_philo, &(p->phi[0])))
			ph_error("Failed to create thread", p);
		while (p->death == false)
			usleep(0);
		return;
	}
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
		i++;
	}
}

//start the checkers
void	*routine(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	phi->last_meal = get_time(p);
	if (pthread_create(&(phi->th_checker), NULL, &checker, phi))
		ph_error("Failed to create thread", p);
	while (p->death == false && p->max_meals < p->number_of_philosophers)
	{
		philo_eat(phi);
		ph_print("is sleeping", phi->index, p);
		usleep(p->time_to_sleep * (long)1000);
		ph_print("is thinking", phi->index, p);
	}
	if (pthread_join(phi->th_checker, NULL))
		ph_error("Failed to join thread", p);
	return (NULL);
}

//feed philosophers
void	philo_eat(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	forks(phi, LOCK);
	pthread_mutex_lock(&(phi->checker_mutex));
	phi->last_meal = get_time(phi->philo);
	phi->times_eaten++;
	ph_print("is eating", phi->index, phi->philo);
	usleep(p->time_to_eat * (long)1000);
	pthread_mutex_unlock(&(phi->checker_mutex));
	forks(phi, UNLOCK);
}

//take the forks
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

void	*one_philo(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	phi->last_meal = get_time(p);
	pthread_mutex_lock(&(phi->checker_mutex));
	pthread_mutex_lock(&(p->forks[phi->index]));
	ph_print("has taken a fork", phi->index, p);
	pthread_mutex_unlock(&(p->forks[phi->index]));
	pthread_mutex_unlock(&(phi->checker_mutex));
	if (pthread_create(&(phi->th_checker), NULL, &checker, phi))
		ph_error("Failed to create thread", p);
	if (pthread_join(phi->th_checker, NULL))
		ph_error("Failed to join thread", p);
	pthread_detach(p->phi[0].th);
	return (NULL);
}
