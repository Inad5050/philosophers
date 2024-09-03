/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:00:38 by dani              #+#    #+#             */
/*   Updated: 2024/09/03 16:58:17 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//check if args are positive numbers
int	parsing(t_philo	*p, char **argv)
{
	int	i;
	int	x;

	i = 1;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (!('0' <= argv[i][x] && argv[i][x] <= '9'))
				return (ph_error("Incorrect arguments", p), 0);
			x++;
		}
		i++;
	}
	return (1);
}

//fill struct philo
int	initiate_struct_philo(t_philo *p, int argc, char **argv)
{
	p->number_of_philosophers = ft_atoi(argv[1]);
	p->time_to_die = (unsigned long)ft_atoi(argv[2]);
	p->time_to_eat = (unsigned long)ft_atoi(argv[3]);
	p->time_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		p->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (p->number_of_philosophers < 1 || p->time_to_die < 0 || \
	p->time_to_eat < 0 || p->time_to_sleep < 0 || (argc == 6 && \
	p->number_of_times_each_philosopher_must_eat < 0))
		return (ph_error("Incorrect args", p), 0);
	if (!initiate_struct_phi(p))
		return (0);
	if (!initiate_mutex(p))
		return (0);
	if (pthread_mutex_init(&(p->death_mutex), NULL))
		pthread_mutex_destroy(&(p->death_mutex));
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
		p->phi[i].index = 1;
		p->phi[i].philo = p;
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
