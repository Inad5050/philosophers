/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:00:38 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 10:26:54 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parsing(t_philo	*p, int argc, char **argv)
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
				return (0);
			x++;
		}
		i++;
	}
	return (1);
}

void	initiate_struct_philo(t_philo	*p, int argc, char **argv)
{
	p->number_of_philosophers = argv[1];
	p->time_to_die = argv[2];
	p->time_to_eat = argv[3];
	p->time_to_sleep = argv[4];
	if (argc == 6)
		p->number_of_philosophers = argv[5];
	get_time(p);
	if (!p->current_time)
		p->init_time = p->current_time;	
	initiate_struct_phi(p);
}

void	initiate_struct_phi(t_philo	*p)
{
	int	i;

	i = 0;
	p->phi = ft_calloc(p->number_of_philosophers, sizeof(t_phisolopher));
	if (!p->phi)
		return (ph_error("Cannot allocate memory for t_phisolopher\n", p));
	while (i < p->number_of_philosophers)
		p->phi[i].th = i++;
}

void	get_time(t_philo *p)
{
	struct timeval	*tv;
	if (gettimeofday(&(tv), NULL))
		return (ph_error("Cannot execute gettimeofday\n", p));
	p->current_time = tv->tv_usec;
}