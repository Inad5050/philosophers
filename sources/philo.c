/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 10:49:30 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philosophers(t_philo *p)
{
    pthread_mutex_init(&(p->mutex), NULL);
    while (p->i < p->number_of_philosophers)
	{
        if (pthread_create(&(p->phi[p->i].th), NULL, &routine, p) != 0) 
            return (ph_error("Failed to create thread", p), 0);
        p->i++;
    }    
    p->i = 0;
	while (p->i < p->number_of_philosophers)
	{
        if (pthread_join(&(p->phi[p->i].th), NULL) != 0) 
            return (ph_error("Failed to join thread", p), 0);
        p->i++;
    }
    pthread_mutex_destroy(&(((t_philo*)p)->mutex));
    return (1);
}

void* routine(void *p_structure)
{
    t_philo         *p;
    int             i;

    p = (t_philo*)p_structure;
    i = p->i;
    while (1)
    {
        pthread_mutex_lock(&((p)->mutex));
        get_time(p);
        p->phi[i].previous_meal = p->phi[i].last_meal;
        p->phi[i].last_meal = p->current_time;
        printf("philosopher[%i] has eaten\n", i);    
        if (!philo_dead(p, i))
            p->death = true;
        if (p->death == true)
        {
            pthread_mutex_unlock(&((p)->mutex));
            break ;
        }            
        pthread_mutex_unlock(&((p)->mutex));
    }        
	return (NULL);
}

int    philo_dead(t_philo *p, int i)
{
    if (!(p->phi[i].time_since_meal))
        p->phi[i].time_since_meal = p->phi[i].last_meal - p->init_time;
    else
        p->phi[i].time_since_meal = p->phi[i].last_meal - p->phi[i].previous_meal;
    if (p->phi[i].time_since_meal >= p->time_to_die)
    {
        printf("philosopher[%i] has died\n", i);
        return (0);
    }
    return (1);
}
