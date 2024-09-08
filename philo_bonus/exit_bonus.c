/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 00:28:12 by dani             ###   ########.fr       */
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
				sem_unlink(p->phi[i].checker_sem_name);
			if (p->phi[i].checker_sem_name)
				free(p->phi[i].checker_sem_name);
			i++;
		}
		free(p->phi);
	}
	if (p->forks_sem_created)
		sem_unlink("/forks_sem");
	if (p->write_sem_created)
		sem_unlink("/write_sem");
	if (p)
		free(p);
}
