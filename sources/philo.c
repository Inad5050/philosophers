/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 12:50:51 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//initialize threads & end them
void	philosophers(t_philo *p)
{
    p->i = 0;
    while (p->i < p->number_of_philosophers)
	{
        if (pthread_create(&(p->phi[p->i].th), NULL, &routine, p)) 
            ph_error("Failed to create thread", p);
        p->i++;
    }
    p->i = 0;
	while (p->i < p->number_of_philosophers)
	{
        if (pthread_join(p->phi[p->i].th, NULL))
            ph_error("Failed to join thread", p);
        p->i++;
    }
}

//make philosphers take the forks, eat, sleep, think and die
void* routine(void *p_structure)
{
    t_philo         *p;
    int             i;

    p = (t_philo*)p_structure;
    i = p->i;
    while (1)
    {
        pthread_mutex_lock(&((p)->mutex[i]));
        philo_dead(p, i);
        if (p->death == true)
            break;
        printf("%lu %i has taken a fork\n", p->current_time , i);
        get_time(p);
        philo_eat(p, i);
        usleep(p->time_to_eat);        
        pthread_mutex_unlock(&((p)->mutex[i]));
        printf("%lu %i is sleeping\n", p->current_time , i);
        usleep(p->time_to_sleep);        
    }        
	return (NULL);
}

//make philosphers eat
void    philo_eat(t_philo *p, int i)
{
    p->phi[i].previous_meal = p->phi[i].last_meal;
    p->phi[i].last_meal = p->current_time;
    printf("%lu %i is eating\n", p->current_time , i);
}

//make philosphers die
void    philo_dead(t_philo *p, int i)
{
    if (!(p->phi[i].time_since_meal))
        p->phi[i].time_since_meal = p->phi[i].last_meal - p->init_time;
    else
        p->phi[i].time_since_meal = p->phi[i].last_meal - p->phi[i].previous_meal;
    if (p->phi[i].time_since_meal >= p->time_to_die)
    {
        printf("%lu %i died\n", p->current_time , i);
        p->death = true;
    }
}
