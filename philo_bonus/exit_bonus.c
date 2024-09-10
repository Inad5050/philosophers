/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/10 14:23:15 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//exit the function with an error message
void	ph_error(char *str, t_philo *p)
{
	printf("%s\n", str);
	free_memory(p);
}

//check allocated memory and free it
void	free_memory(t_philo *p)
{
	int	i;

	i = 0;
	if (p->phi)
	{
		while (i < p->number_of_philosophers)
		{
			if (p->phi[i].checker_sem_created)
				close_semaphores(p->phi[i].checker_sem, \
				p->phi[i].checker_sem_name);
			if (p->phi[i].checker_sem_name)
				free(p->phi[i].checker_sem_name);
			i++;
		}
		free(p->phi);
	}
	if (p->forks_sem_created)
		close_semaphores(p->forks_sem, "/forks_sem");
	if (p->write_sem_created)
		close_semaphores(p->write_sem, "/write_sem");
	if (p)
		free(p);
}

void	close_semaphores(sem_t *sem, char *sem_name)
{
	sem_close(sem);
	sem_unlink(sem_name);	
}