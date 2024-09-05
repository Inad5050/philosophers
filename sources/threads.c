/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/05 03:01:23 by dani             ###   ########.fr       */
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
	stop_condition(p);
	i = 0;
	while (i < p->number_of_philosophers)
	{	

		printf("preJOINED %i\n", p->phi[i].index);
		
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
	while (p->death == false && p->max_meals == false)
	{
		forks(phi, LOCK);
		if (!philo_eat(phi))
		{
			forks(phi, UNLOCK);
			break;
		}
		forks(phi, UNLOCK);
		ph_print("is sleeping", phi->index, p);
		usleep(p->time_to_sleep);
		ph_print("is thinking", phi->index, p);
	}
	return (NULL);
}

//philosophers take the forks
void	forks(t_phisolopher *phi, int i)
{
	t_philo	*p;

	p = phi->philo;
	if (i == LOCK)
	{
		pthread_mutex_lock(&(p->mutex[phi->index]));
		ph_print("has taken a fork", phi->index, p);
		if (phi->index != p->number_of_philosophers - 1)
			pthread_mutex_lock(&(p->mutex[phi->index + 1]));
		else
			pthread_mutex_lock(&(p->mutex[0]));
		ph_print("has taken a fork", phi->index, p);
	}
	if (i == UNLOCK)
	{
		pthread_mutex_unlock(&(p->mutex[phi->index]));
		if (phi->index != p->number_of_philosophers)
			pthread_mutex_unlock(&(p->mutex[phi->index + 1]));
		else
			pthread_mutex_unlock(&(p->mutex[0]));
	}
}

int	philo_eat(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	pthread_mutex_lock(&(p->death_mutex));
	if (p->death == false)
	{
		phi->last_meal = get_time(phi->philo);		
		ph_print("is eating", phi->index, phi->philo);
		phi->times_eaten++;
		usleep(p->time_to_eat);
		pthread_mutex_unlock(&(p->death_mutex));
		return (pthread_mutex_unlock(&(p->death_mutex)), 1);
	}
	else
		return (pthread_mutex_unlock(&(p->death_mutex)), 0);
}
