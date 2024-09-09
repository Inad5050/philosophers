/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 01:03:53 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//start the process and wait for all of them
void	start_process(t_philo *p)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		pid = fork();
		if (pid < 0)
			ph_error("Cannot fork()", p);
		if (!pid)
		{
			routine(&(p->phi[i]));
			break;
		}
		i++;
	}
	waitpid(-1, NULL, 0);
}

//start the checkers
void	routine(t_phisolopher	*phi)
{
	t_philo	*p;

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
	sem_close(p->forks_sem);
	sem_close(p->write_sem);
	sem_close(phi->checker_sem);
	
	printf("ROUTINE termina index = %i\n", phi->index);	
}

//feed philosophers
void	philo_eat(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	forks(phi, LOCK);
	sem_wait(phi->checker_sem);	
	phi->last_meal = get_time(phi->philo);
	ph_print("is eating", phi->index, phi->philo);
	ft_usleep(p->time_to_eat, p);
	phi->times_eaten++;
	sem_post(phi->checker_sem);	
	forks(phi, UNLOCK);
}

//take the forks
void	forks(t_phisolopher *phi, int i)
{
	t_philo	*p;

	p = phi->philo;
	if (i == LOCK)
	{
		sem_wait(p->forks_sem);
		ph_print("has taken a fork", phi->index, p);
		sem_wait(p->forks_sem);
		ph_print("has taken a fork", phi->index, p);
	}
	if (i == UNLOCK)
	{
		sem_post(p->forks_sem);	
		sem_post(p->forks_sem);	
	}
}
