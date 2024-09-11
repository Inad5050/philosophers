/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/11 21:19:51 by dangonz3         ###   ########.fr       */
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
			ft_usleep(0, p);
		return ;
	}
	i = 0;
	while (i < p->number_of_philosophers)
	{
		if (pthread_create(&(p->phi[i].th), NULL, &routine, &(p->phi[i])))
			ph_error("Failed to create thread", p);
		ft_usleep(1, p);
		i++;
	}
	end_threads(p);
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
	while (p->death == false && p->full == false)
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
	phi->times_eaten++;
	ph_print("is eating", phi->index, phi->philo);
	ft_usleep(p->time_to_eat, p);
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

void	end_threads(t_philo *p)
{
	int	i;

	if (p->number_of_times_each_philosopher_must_eat)
	{
		while (p->death == false && p->full == false)
		{
			pthread_mutex_lock(&(p->end_condition_mutex));
			if (p->max_meals == p->number_of_philosophers)
			{
				pthread_mutex_lock(&(p->write_mutex));
				p->full = true;
				printf("%lu all philosophers are full\n", \
					get_time(p) - p->initial_time);
				pthread_mutex_unlock(&(p->write_mutex));
			}
			pthread_mutex_unlock(&(p->end_condition_mutex));
			if ((p->death == false && p->full == false))
				ft_usleep(5, p);
		}
	}
	i = 0;
	while (i < p->number_of_philosophers)
	{
		if (pthread_join(p->phi[i].th, NULL))
			ph_error("Failed to join thread", p);
		i++;
	}
}
