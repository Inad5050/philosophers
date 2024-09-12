/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:06:24 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 20:18:56 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initiate_semaphores(t_philo	*p)
{
	if (!create_semaphore("/forks_sem", p->number_of_philosophers, \
	&(p->forks_sem), p))
		return (ph_error("Cannot create sem /forks_sem\n", p), 0);
	p->forks_sem_created = true;
	if (!create_semaphore("/write_sem", 1, &(p->write_sem), p))
		return (ph_error("Cannot create sem /write_semn", p), 0);
	p->write_sem_created = true;
	if (!initiate_struct_phi(p))
		return (0);
	return (1);
}

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
		p->phi[i].eat_sem_name = ph_strjoin("/eat_sem_", i + '0');
		if (!p->phi[i].eat_sem_name)
			return (ph_error("Cannot ph_strjoin eat_sem_name\n", p), 0);
		if (!create_semaphore(p->phi[i].eat_sem_name, 1, &(p->phi[i].eat_sem), p))
			return (ph_error("Cannot create eat_sem\n", p), 0);
		p->phi[i].eat_sem_created = true;
		p->phi[i].end_sem_name = ph_strjoin("/end_sem_", i + '0');
		if (!p->phi[i].end_sem_name)
			return (ph_error("Cannot ph_strjoin end_sem_name\n", p), 0);
		if (!create_semaphore(p->phi[i].end_sem_name, 1, &(p->phi[i].end_sem), p))
			return (ph_error("Cannot create end_sem\n", p), 0);
		p->phi[i].end_sem_created = true;
		i++;
	}
	return (1);
}

int	create_semaphore(char *str, int nmb, sem_t **sem, t_philo *p)
{
	*sem = sem_open(str, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, nmb);
	if (*sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_unlink(str);
			create_semaphore(str, nmb, sem, p);
		}
		else
			return (0);
	}
	return (1);
}
