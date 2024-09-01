/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:00:38 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 12:43:15 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//check if args are positive numbers
int	parsing(t_philo	*p, char **argv)
{
	int	i;
	int	x;

	i = 1;
	x = 1;
	while (argv[i])
	{
		while (argv[i][x])
		{
			if (!('0' < argv[i][x] && argv[i][x] > '9'))
				return (ph_error("Incorrect arguments", p), 0);
			x++;
		}
		i++;
	}
	return (1);
}

//fill struct philo
int	initiate_struct_philo(t_philo	*p, int argc, char **argv)
{
	p->number_of_philosophers = ft_atoi(argv[1]);
	p->time_to_die = (unsigned long)ft_atoi(argv[2]);
	p->time_to_eat = (unsigned long)ft_atoi(argv[3]);
	p->time_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		p->number_of_philosophers = ft_atoi(argv[5]);
	get_time(p);
	if (!p->current_time)
		p->init_time = p->current_time;
	if (!initiate_struct_phi(p))
		return (0);
	if (!initiate_mutex(p))
		return (0);
	return (1);
}

//fill struct phi
int	initiate_struct_phi(t_philo	*p)
{
	int	i;

	i = 0;
	p->phi = ft_calloc(p->number_of_philosophers, sizeof(t_phisolopher));
	if (!p->phi)
		return (ph_error("Cannot allocate memory for t_phisolopher\n", p), 0);
	while (i < p->number_of_philosophers)
	{
		p->phi[i].th = i;
		i++;
	}
	return (1);
}

//start the mutexs
int	initiate_mutex(t_philo	*p)
{
	int	i;
	int	x;

	i = 0;	
	x = 0;	
	p->mutex = ft_calloc(p->number_of_philosophers + 1, sizeof(pthread_mutex_t));
	if (!p->mutex)
		ph_error("Cannot allocate memory for p->mutex\n", p);	
	while (i < p->number_of_philosophers)
	{
		if (pthread_mutex_init(&(p->mutex[i]), NULL))
		{			
			while(x < i)
				pthread_mutex_destroy(&(p->mutex[x]));
			free(p->mutex);
			return (ph_error("Failed to initiate mutex\n", p), 0);
		}
		i++;
	}
	return (1);
}
