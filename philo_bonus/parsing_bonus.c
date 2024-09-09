/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:00:38 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 01:53:16 by dani             ###   ########.fr       */
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
	if (!initiate_sems(p))
		return (0);
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
	int		i;

	i = 0;
	p->phi = ft_calloc(p->number_of_philosophers, sizeof(t_phisolopher));
	if (!p->phi)
		return (ph_error("Cannot allocate memory for t_phisolopher\n", p), 0);
	while (i < p->number_of_philosophers)
	{
		p->phi[i].index = i;
		p->phi[i].philo = p;
		p->phi[i].checker_sem_name = ph_strjoin("/checker_sem", i + '0');
		if (!p->phi[i].checker_sem_name)
			return (ph_error("Cannot ph_strjoin checker_sem_name\n", p), 0);
		p->phi[i].checker_sem = sem_open(p->phi[i].checker_sem_name, \
		O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
		if (p->phi[i].checker_sem == SEM_FAILED)
			return (ph_error("Cannot create checker_sem\n", p), 0);
		p->phi[i].checker_sem_created = true;
		i++;
	}
	return (1);
}

//create sems
int	initiate_sems(t_philo	*p)
{
	p->forks_sem = sem_open("/forks_sem", \
	O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, p->number_of_philosophers);
	if (p->forks_sem == SEM_FAILED)
		return (ph_error("Cannot create forks_sem\n", p), 0);
	p->forks_sem_created = true;
	p->write_sem = sem_open("/write_sem", \
	O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (p->write_sem == SEM_FAILED)
		return (ph_error("Cannot create forks_sem\n", p), 0);
	p->write_sem_created = true;		
	return (1);
}
