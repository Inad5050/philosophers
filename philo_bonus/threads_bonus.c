/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 20:41:59 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_process(t_philo *p)
{
	int		i;
	pid_t	pid;

	i = 0;
	p->initial_time = get_time(p);
	if (p->number_of_philosophers == 1)
	{
		one_philo(p);
		return ;
	}
	while (i < p->number_of_philosophers)
	{
		pid = fork();
		if (pid < 0)
			ph_error("Cannot fork()", p);
		if (!pid)
		{
			routine(&(p->phi[i]));
			break ;
		}
		else
			p->phi[i].pid = pid;
		i++;
	}
	end_process(p);
}

void	routine(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	phi->last_meal = get_time(p);
	if (pthread_create(&(phi->th_checker), NULL, &checker_routine, phi))
		ph_error("Failed to create thread", p);
	if (phi->index % 2 != 0)
		ph_usleep(10, p);
	while (check_end_condition(phi))
	{
		philo_eat(phi);
		ph_print("is sleeping", phi);
		ph_usleep(p->time_to_sleep, p);
		ph_print("is thinking", phi);
	}
	if (pthread_join(phi->th_checker, NULL))
		ph_error("Failed to join thread", p);
}

void	philo_eat(t_phisolopher *phi)
{
	t_philo	*p;

	p = phi->philo;
	forks(phi, LOCK);
	ph_print("is eating", phi);
	phi->eating = true;
	sem_wait(phi->eat_sem);
	phi->last_meal = get_time(phi->philo);
	phi->times_eaten++;
	sem_post(phi->eat_sem);
	ph_usleep(p->time_to_eat, p);
	phi->eating = false;
	forks(phi, UNLOCK);
}

void	forks(t_phisolopher *phi, int i)
{
	t_philo	*p;

	p = phi->philo;
	if (i == LOCK)
	{
		sem_wait(p->forks_sem);
		ph_print("has taken a fork", phi);
		sem_wait(p->forks_sem);
		ph_print("has taken a fork", phi);
	}
	if (i == UNLOCK)
	{
		sem_post(p->forks_sem);
		sem_post(p->forks_sem);
	}
}

void	end_process(t_philo *p)
{
	int		i;
	pid_t	finished_pid;

	if (!p->number_of_times_each_philosopher_must_eat)
	{
		finished_pid = waitpid(-1, NULL, 0);
		i = 0;
		if (finished_pid > 0)
		{
			while (i < p->number_of_philosophers)
			{
				if (p->phi[i].pid != finished_pid)
					kill(p->phi[i].pid, SIGKILL);
				i++;
			}
		}
	}
	while (wait(NULL) > 0)
		continue ;
}
