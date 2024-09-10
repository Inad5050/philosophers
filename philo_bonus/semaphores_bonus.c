/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:06:24 by dani              #+#    #+#             */
/*   Updated: 2024/09/11 01:13:15 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initiate_semaphores(t_philo	*p)
{
	if (!create_semaphore("/forks_sem", p->number_of_philosophers, \
	&(p->forks_sem), p))
		return (ph_error("Cannot create sem /forks_sem\n", p), 0);
	p->forks_sem_created = true;
	if (!create_semaphore("/write_sem", 1, &(p->write_sem), p))
		return (ph_error("Cannot create sem /write_semn", p), 0);
	p->write_sem_created = true;
	if (!initiate_struct_phi(p))
		return (0);
	return (1);
}

int	initiate_struct_phi(t_philo	*p)
{
	int		i;

	i = 0;
	p->phi = ft_calloc(p->number_of_philosophers, sizeof(t_phisolopher));
	if (!p->phi)
		return (ph_error("Cannot allocate memory for t_phisolopher\n", p), 0);
	while (i < p->number_of_philosophers)
	{
		p->phi[i].index = i;
		p->phi[i].philo = p;
		p->phi[i].checker_sem_name = ph_strjoin("/checker_sem_", i + '0');
		if (!p->phi[i].checker_sem_name)
			return (ph_error("Cannot ph_strjoin checker_sem_name\n", p), 0);
		if (!create_semaphore(p->phi[i].checker_sem_name, 1, \
		&(p->phi[i].checker_sem), p))
			return (ph_error("Cannot create checker_sem\n", p), 0);
		p->phi[i].checker_sem_created = true;
		i++;
	}
	return (1);
}

int	create_semaphore(char *str, int nmb, sem_t **sem, t_philo *p)
{
	*sem = sem_open(str, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, nmb);
	if (*sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_unlink(str);
			create_semaphore(str, nmb, sem, p);
		}
		else
			return (0);
	}
	return (1);
}

//special case for philos == 1
void	one_philo(t_philo *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ph_error("Cannot fork()", p);
	if (!pid)
	{
		p->phi[0].last_meal = get_time(p);
		if (pthread_create(&(p->phi[0].th_checker), NULL, \
		&checker, &(p->phi[0])))
			ph_error("Failed to create thread", p);
		sem_wait(p->forks_sem);
		ph_print("has taken a fork", p->phi[0].index, p);
		while (p->death == false)
			usleep(0);
		if (pthread_join(p->phi[0].th_checker, NULL))
			ph_error("Failed to join thread", p);
		exit(0);
	}
	wait(NULL);
}
