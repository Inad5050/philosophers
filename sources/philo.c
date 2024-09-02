/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/02 20:54:39 by dani             ###   ########.fr       */
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
    unsigned long	current_time;

    p = (t_philo*)p_structure;
    i = p->i;
    while (1)
    {
        pthread_mutex_lock(&((p)->mutex[i]));
        if (i != p->number_of_philosophers)
            pthread_mutex_lock(&((p)->mutex[i + 1]));
        else
            pthread_mutex_lock(&((p)->mutex[0]));
        current_time = get_time(p);
        if (!philo_dead(p, i, current_time))
            break;
        printf("%lu %i has taken a fork\n", current_time , i);
        philo_eat(p, i, current_time);
        usleep(p->time_to_eat);        
        pthread_mutex_unlock(&((p)->mutex[i]));
        if (i != p->number_of_philosophers)
            pthread_mutex_unlock(&((p)->mutex[i + 1]));
        else
            pthread_mutex_unlock(&((p)->mutex[0]));
        printf("%lu %i is sleeping\n", current_time , i);
        usleep(p->time_to_sleep);        
    }        
	return (NULL);
}

//make philosphers eat
void    philo_eat(t_philo *p, int i, unsigned long current_time)
{
    p->phi[i].previous_meal = p->phi[i].last_meal;
    p->phi[i].last_meal = current_time;
    printf("%lu %i is eating\n", current_time , i);
}

//make philosphers die
int    philo_dead(t_philo *p, int i, unsigned long current_time)
{
    if (!(p->phi[i].time_since_meal))
        p->phi[i].time_since_meal = p->phi[i].last_meal - p->init_time;
    else
        p->phi[i].time_since_meal = p->phi[i].last_meal - p->phi[i].previous_meal;
    pthread_mutex_lock(&(p->death_mutex));    
    if (p->death == true)
        return (0);
    if (p->phi[i].time_since_meal >= p->time_to_die)
    {
        printf("%lu %i died\n", current_time , i);
        p->death = true;
        return (0);
    }
    pthread_mutex_unlock(&(p->death_mutex));
    return (1);
}
