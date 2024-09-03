/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:02:17 by dani              #+#    #+#             */
/*   Updated: 2024/09/03 17:35:13 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//initialize threads & end them
void	philosophers(t_philo *p)
{
    int i;
    
    i = 0;
    p->initial_time = get_time(p);
    while (i < p->number_of_philosophers)
	{     
        p->phi[i].last_meal = get_time(p);
        if (!p->phi[i].last_meal)
            ph_error("Couldn't get_time", p); 
        if (pthread_create(&(p->phi[i].th), NULL, &routine, &(p->phi[i]))) 
            ph_error("Failed to create thread", p);
        i++;
    }
    philo_dead(p);    
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
    t_philo *p;

    p = phi->philo;
    phi->last_meal = current_time;
    phi->times_eaten++;
    ph_print("is eating", i, p);
    if (p->phi[i].times_eaten <= p->number_of_times_each_philosopher_must_eat && \
    p->number_of_times_each_philosopher_must_eat)
        phi->max_meals = true;
}

//make philosphers die
void    philo_dead(t_philo *p)
{
    int i;
    
    i = 0;
    while(p->death == false || !max_meals(p))
    {
        while ((p->phi[i].times_eaten <= p->number_of_times_each_philosopher_must_eat || \
        !p->number_of_times_each_philosopher_must_eat) && p->death == false)
        {            
            if (p->phi[i].last_meal - get_time(p) >= p->time_to_die)
            {
                pthread_mutex_lock(&(p->death_mutex)); 
                p->death = true;
                ph_print("has died", i, p);
                pthread_mutex_unlock(&(p->death_mutex));
            }
            i++;
        }
        if (i == p->number_of_philosophers - 1)
            i = 0;       
    }
}

int    max_meals(t_philo *p)
{   
    int i;
    
    i = 0;
    while (p->phi[i++].max_meals == true)
    {
        if (i == p->number_of_philosophers - 1)
            return (0);
    }
    return (1);
}