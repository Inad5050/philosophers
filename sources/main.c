/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:02:23 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 15:21:39 by dani             ###   ########.fr       */
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
	if (!parsing(p, argv))
		return (1);
	if (!initiate_struct_philo(p, argc, argv))
		return (1);
	philosophers(p);
	free_memory(p);
	return (0);
}
