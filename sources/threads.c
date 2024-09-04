/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/04 18:15:50 by dani             ###   ########.fr       */
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

    phi = (t_phisolopher*)philosopher_struct;
    p = phi->philo;    
    while (p->death == false && p->max_meals == false)
    {
        use_mutex(phi, LOCK);
        /* pthread_mutex_lock(&(p->meal_mutex)); */
        phi->last_meal = get_time(phi->philo);
        phi->times_eaten++;
        ph_print("is eating", phi->index, phi->philo);
        usleep(p->time_to_eat);
        /* pthread_mutex_unlock(&(p->meal_mutex)); */
        use_mutex(phi, UNLOCK);
        ph_print("is sleeping", phi->index, p);
        usleep(p->time_to_sleep);
        ph_print("is thinking", phi->index, p);   
    }
    return (NULL);
}

//philosophers take the forks
void    use_mutex(t_phisolopher *phi, int i)
{
    t_philo *p;

    p = phi->philo;
    if (i == LOCK)
    {
        pthread_mutex_lock(&(p->mutex[phi->index]));
        ph_print("has taken a fork", phi->index, p);
        if (phi->index != p->number_of_philosophers - 1)
            pthread_mutex_lock(&(p->mutex[phi->index + 1]));
        else
            pthread_mutex_lock(&(p->mutex[0]));
        ph_print("has taken a fork", phi->index, p);       
    }
    if (i == UNLOCK)
    {
        pthread_mutex_unlock(&(p->mutex[phi->index]));
        if (phi->index != p->number_of_philosophers)
            pthread_mutex_unlock(&(p->mutex[phi->index + 1]));
        else
            pthread_mutex_unlock(&(p->mutex[0]));
    }    
}
