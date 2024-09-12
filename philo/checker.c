/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:52:23 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/12 15:28:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker_routine(void *p_struct)
{
	t_philo	*p;

	p = (t_philo *)p_struct;
	ph_usleep(2, p);
	while (1)
	{
		if (!check_death(p) || !check_max_meals(p))
			break ;
	}
	return (p_struct);
}

int	check_death(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		pthread_mutex_lock(&p->eat_mutex);
		if (get_time(p) - p->phi[i].last_meal >= p->time_to_die \
		&& p->phi[i].eating == false)
		{
			activate_end_condition(p);
			ph_print("died", i, p);
			pthread_mutex_unlock(&p->eat_mutex);
			return (0);
		}
		i++;
		pthread_mutex_unlock(&p->eat_mutex);
	}
	return (1);
}

int	check_max_meals(t_philo *p)
{
	int	i;
    int max_meals;
    
	i = 0;
	max_meals = 0;
	if (!p->number_of_times_each_philosopher_must_eat)
		return (1);
	while (i < p->number_of_philosophers)
	{
		pthread_mutex_lock(&(p->eat_mutex));
		if (p->phi[i].times_eaten >= p->number_of_times_each_philosopher_must_eat)
			max_meals++;
		i++;
		pthread_mutex_unlock(&(p->eat_mutex));
	}
	if (max_meals == p->number_of_philosophers)
	{
		activate_end_condition(p);
		return (0);
	}
	return (1);
}

void	activate_end_condition(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		pthread_mutex_lock(&(p->end_condition_mutex));
		p->phi[i].end_condition = true;
		i++;
		pthread_mutex_unlock(&(p->end_condition_mutex));
	}
}
