/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:02:23 by dani              #+#    #+#             */
/*   Updated: 2024/09/06 01:28:22 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*p;

	if (argc != 5 && argc != 6)
		return (printf("Invalid argument number\n"), 1);
	p = ft_calloc(1, sizeof(t_philo));
	if (!p)
		return (printf("Cannot allocate memory for t_philo\n"), 1);
	if (!parsing(p, argc, argv))
		return (1);
	/* print_everything(p); */
	/* printf("COMPLETADO parsing\n"); */
	start_threads(p);
	/* printf("COMPLETADO start_threads\n"); */
	free_memory(p);
	/* printf("COMPLETADO free_memory\n"); */
	return (0);
}

void	print_everything(t_philo *p)
{
	printf("START print_everything\n");
	printf("number_of_philosophers = %i\n", p->number_of_philosophers);
	printf("time_to_die = %ld\n", p->time_to_die);
	printf("time_to_eat = %ld\n", p->time_to_eat);
	printf("time_to_sleep = %ld\n", p->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat = %i\n", p->number_of_times_each_philosopher_must_eat);
	printf("initial_time = %ld\n", p->initial_time);
	printf("write_mutex_initialized = %i\n", p->write_mutex_initialized);
	printf("death = %i\n", p->death);
	printf("max_meals = %i\n", p->max_meals);
	int	i = 0;
	while (i < p->number_of_philosophers)
	{
		printf("p->phi[%i].index = %i\n", i, p->phi[i].index);
		printf("p->phi[%i].th = %lu\n", i, p->phi[i].th);
		printf("p->phi[%i].last_meal = %ld\n", i, p->phi[i].last_meal);
		printf("p->phi[%i].times_eaten = %i\n", i, p->phi[i].times_eaten);
		printf("p->phi[%i].th_checker = %lu\n", i, p->phi[i].th_checker);
		printf("p->phi[%i].checker_mutex_initialized = %i\n", i, p->phi[i].checker_mutex_initialized);
		printf("p->phi[%i].philo = %p\n", i, p->phi[i].philo);
		i++;
	}
	printf("END print_everything\n");
}