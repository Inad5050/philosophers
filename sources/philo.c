/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/03 14:56:57 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//initialize threads & end them
void	philosophers(t_philo *p)
{
    int i;
    
    i = 0;
    while (i < p->number_of_philosophers)
	{     
        p->phi[i].last_meal = get_time();
        if (!p->phi[i].last_meal)
            ph_error("Couldn't get_time", p); 
        if (pthread_create(&(p->phi[i].th), NULL, &routine, &(p->phi[i]))) 
            ph_error("Failed to create thread", p);
        i++;
    }
    philo_dead(p, i);    
    i = 0;
	while (i < p->number_of_philosophers)
	{
        printf("HELLO2\n");
        if (pthread_join(p->phi[i].th, NULL))
            ph_error("Failed to join thread", p);
        i++;
    }
    printf("HELLO3\n");
}

//make philosphers take the forks, eat, sleep, think and die
void* routine(void *philo)
{
    t_phisolopher   *phi;
    int             i;
    unsigned long	current_time;

    phi = (t_phisolopher*)philo;
    
    printf("routine PHILO: %i\n", i);
    
    while (1)
    {
        current_time = get_time();
        pthread_mutex_lock(&((p)->mutex[i]));
        if (i != p->number_of_philosophers)
            pthread_mutex_lock(&((p)->mutex[i + 1]));
        else
            pthread_mutex_lock(&((p)->mutex[0]));
        printf("%lu %i has taken a fork\n", current_time , i);
        philo_eat(phi, i, current_time);
        usleep(p->time_to_eat);        
        pthread_mutex_unlock(&((p)->mutex[i]));
        if (i != p->number_of_philosophers)
            pthread_mutex_unlock(&((p)->mutex[i + 1]));
        else
            pthread_mutex_unlock(&((p)->mutex[0]));
        if (p->number_of_times_each_philosopher_must_eat && \
        p->phi[i].times_eaten >= p->number_of_times_each_philosopher_must_eat)
            return (printf("%lu %i has eaten enough\n", current_time , i), NULL);
        printf("%lu %i is sleeping\n", current_time , i);
        usleep(p->time_to_sleep);        
    }        
}

//make philosphers eat
void    philo_eat(t_phisolopher *phi, int i, unsigned long current_time)
{
/*     phi->previous_meal = phi->last_meal; */
    phi->last_meal = current_time;
    phi->times_eaten++;
    printf("%lu %i is eating\n", current_time , i);
}

//make philosphers die
void    philo_dead(t_philo *p)
{
    int i;
    
    i = 0;
    while((p->phi[i].times_eaten <= p->number_of_times_each_philosopher_must_eat || \
    !p->number_of_times_each_philosopher_must_eat) && p->death == false)
    {
        while ((p->phi[i].times_eaten <= p->number_of_times_each_philosopher_must_eat || \
        !p->number_of_times_each_philosopher_must_eat) && p->death == false)
        {            
            if (p->phi[i].last_meal - get_time() >= p->time_to_die)
            {
                pthread_mutex_lock(&(p->death_mutex)); 
                p->death = true;
                printf("%lu %i has died", get_time(), i);
                pthread_mutex_unlock(&(p->death_mutex));
            }
            i++;
        }
        if (i == p->number_of_philosophers)
            i = 0;
    }
}
