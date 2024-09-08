/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:00:38 by dani              #+#    #+#             */
/*   Updated: 2024/09/08 01:44:40 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parsing(t_philo	*p, int argc, char **argv)
{
	if (!check_args(p, argv))
		return (0);
	if (!initiate_args(p, argc, argv))
		return (0);
	p->initial_time = get_time(p);
	if (!initiate_struct_phi(p))
		return (0);
	if (!initiate_forks(p))
		return (0);
	if (pthread_mutex_init(&(p->write_mutex), NULL))
		return (ph_error("Cannot initiate write_mutex\n", p), 0);
	p->write_mutex_initialized = true;
	return (1);
}

//check if args are positive numbers
int	check_args(t_philo	*p, char **argv)
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
				return (ph_error("Non-number arguments", p), 0);
			x++;
		}
		i++;
	}
	return (1);
}

//fill struct philo
int	initiate_args(t_philo *p, int argc, char **argv)
{
	p->number_of_philosophers = ft_atoi(argv[1]);
	p->time_to_die = (long)ft_atoi(argv[2]);
	p->time_to_eat = (long)ft_atoi(argv[3]);
	p->time_to_sleep = (long)ft_atoi(argv[4]);
	if (argc == 6)
		p->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (p->number_of_philosophers < 1 || p->time_to_die < 1 || \
	p->time_to_eat < 1 || p->time_to_sleep < 1 || (argc == 6 && \
	p->number_of_times_each_philosopher_must_eat < 1))
		return (ph_error("Arguments must be non-zero positive numbers", p), 0);
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
		p->phi[i].index = i;
		p->phi[i].philo = p;
		if (pthread_mutex_init(&(p->phi[i].checker_mutex), NULL))
			return (ph_error("Cannot initiate meal_mutex\n", p), 0);
		p->phi[i].checker_mutex_initialized = true;
		i++;
	}
	return (1);
}

//start fork_mutexs
int	initiate_forks(t_philo	*p)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	p->forks = ft_calloc(p->number_of_philosophers, sizeof(pthread_mutex_t));
	if (!p->forks)
		ph_error("Cannot allocate memory for p->forks\n", p);
	while (i < p->number_of_philosophers)
	{
		if (pthread_mutex_init(&(p->forks[i]), NULL))
		{
			while (x < i)
				pthread_mutex_destroy(&(p->forks[x++]));
			free(p->forks);
			return (ph_error("Failed to initiate forks\n", p), 0);
		}
		i++;
	}
	return (1);
}
