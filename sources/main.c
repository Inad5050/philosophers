/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:02:23 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 10:39:44 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat] */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*p;

	if (argc != 5 || argc != 6)
		return (printf("Invalid argument number\n"), 0);
	p = ft_calloc(1, sizeof(t_philo));
	if (!p)
		return (printf("Cannot allocate memory for t_philo\n"), 0);
	if (!parsing(p, argc, argv))
		return (ph_error("Incorrect arguments", p), 0);
	initiate_struct(p, argc, argv);
	philosophers(p);
	free_memory(p);
	return (0);
}
