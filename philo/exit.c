/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 15:04:14 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_error(char *str, t_philo *p)
{
	printf("%s\n", str);
	free_memory(p);
}

void	free_memory(t_philo *p)
{
	int	i;

	i = 0;
	if (p->forks)
	{
		while (i < p->number_of_philosophers)
			pthread_mutex_destroy(&(p->forks[i++]));
		free(p->forks);
	}
	if (p->write_mutex_initialized)
		pthread_mutex_destroy(&(p->write_mutex));
	if (p->eat_mutex_initialized)
		pthread_mutex_destroy(&(p->eat_mutex));
	if (p->end_condition_mutex_initialized)
		pthread_mutex_destroy(&(p->end_condition_mutex));
	if (p)
		free(p);
}
