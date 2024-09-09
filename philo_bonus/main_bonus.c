/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:02:23 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 01:27:47 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	*p;
	int		pars;
	
	if (argc != 5 && argc != 6)
		return (printf("Invalid argument number\n"), 1);
	p = ft_calloc(1, sizeof(t_philo));
	if (!p)
		return (printf("Cannot allocate memory for t_philo\n"), 1);
	pars = parsing(p, argc, argv);
	if (pars == 0)
		return (1);
	if (pars == 2)
		return (free_memory(p), 1);
	start_process(p);
	free_memory(p);
	return (0);
}
