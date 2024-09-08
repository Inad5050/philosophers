/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/07 10:11:02 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//start the philosophers and wait for them to finish
void	start_threads(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		if (pthread_create(&(p->phi[i].th), NULL, &routine, &(p->phi[i])))
			ph_error("Failed to create thread", p);
		ft_usleep(1, p);
		i++;
	}
	i = 0;
	if (p->number_of_philosophers == 1)
	{
		pthread_detach(p->phi[0].th);
		while (p->death == false)
			ft_usleep(0, p);
		return ;
	}
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
	while (p->death == false && p->max_meals == false)
	{
		philo_eat(phi);
		ph_print("is sleeping", phi->index, p);
		ft_usleep(p->time_to_sleep, p);
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
	ph_print("is eating", phi->index, phi->philo);
	ft_usleep(p->time_to_eat, p);
	phi->times_eaten++;
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
