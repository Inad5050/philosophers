/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/08 01:44:34 by dani             ###   ########.fr       */
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
			pthread_mutex_destroy(&(p->phi[i++].checker_mutex));
		free(p->phi);
	}
	i = 0;
	if (p->forks)
	{
		while (i < p->number_of_philosophers)
			pthread_mutex_destroy(&(p->forks[i++]));
		free(p->forks);
	}
	if (p->write_mutex_initialized)
		pthread_mutex_destroy(&(p->write_mutex));
	if (p)
		free(p);
}
