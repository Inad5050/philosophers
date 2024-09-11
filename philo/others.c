/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:02:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/11 21:02:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	phi->last_meal = get_time(p);
	pthread_mutex_lock(&(phi->checker_mutex));
	pthread_mutex_lock(&(p->forks[phi->index]));
	ph_print("has taken a fork", phi->index, p);
	pthread_mutex_unlock(&(p->forks[phi->index]));
	pthread_mutex_unlock(&(phi->checker_mutex));
	if (pthread_create(&(phi->th_checker), NULL, &checker, phi))
		ph_error("Failed to create thread", p);
	if (pthread_join(phi->th_checker, NULL))
		ph_error("Failed to join thread", p);
	pthread_detach(p->phi[0].th);
	return (NULL);
}