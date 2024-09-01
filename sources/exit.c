/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/01 09:04:23 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ph_error(char *str, t_philo *p)
{
	printf("%s\n", str);
	free_memory(p);
	return (1);
}

int	free_memory(t_philo *p)
{
	if (p)
		free(p);
	return (1);
}
