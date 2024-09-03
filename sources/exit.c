/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/03 14:44:50 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//exit the function with an error message
int	ph_error(char *str, t_philo *p)
{
	printf("%s\n", str);
	free_memory(p);
	return (1);
}

//check allocated memory and free it
int	free_memory(t_philo *p)
{
	int	i;

	i = 0;
	if (p->phi)
		free(p->phi);
	if (p->mutex)
	{
		while (i < p->number_of_philosophers)
			pthread_mutex_destroy(&(p->mutex[i]));
		free(p->mutex);
	}
	if (p)
		free(p);
	return (1);
}
