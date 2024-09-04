/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/04 14:20:33 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//initialize threads & end them
void	start_threads(t_philo *p)
{
    int i;
    
    i = 0;
    while (i < p->number_of_philosophers)
	{     
        if (!p->phi[i].last_meal)
            ph_error("Couldn't get_time", p); 
        if (pthread_create(&(p->phi[i].th), NULL, &routine, &(p->phi[i]))) 
            ph_error("Failed to create thread", p);
        i++;
    }
    stop_condition(p);
    stop_threads(p);
}

//make philosphers take the forks, eat, sleep and think
void* routine(void *philosopher_struct)
{
    t_phisolopher   *phi;
    t_philo         *p;
    int             i;
    unsigned long	current_time;

    phi = (t_phisolopher*)philosopher_struct;
    p = phi->philo;    
    while (1)
    {
        current_time = get_time(p);
        pthread_mutex_lock(&((p)->mutex[i]));
        if (i != p->number_of_philosophers)
            pthread_mutex_lock(&((p)->mutex[i + 1]));
        else
            pthread_mutex_lock(&((p)->mutex[0]));
        ph_print("has taken a fork", i, p);
        philo_eat(phi, i, current_time);
        usleep(p->time_to_eat);        
        pthread_mutex_unlock(&((p)->mutex[i]));
        if (i != p->number_of_philosophers)
            pthread_mutex_unlock(&((p)->mutex[i + 1]));
        else
            pthread_mutex_unlock(&((p)->mutex[0]));
        ph_print("is sleeping", i, p);
        usleep(p->time_to_sleep);        
    }        
}

//make philosphers eat
void    philo_eat(t_phisolopher *phi, int i, unsigned long current_time)
{
    phi->last_meal = get_time(phi->philo);
    phi->times_eaten++;
    ph_print("is eating", i, phi->philo);
}
