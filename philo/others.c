/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:02:21 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/12 15:31:05 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *phi_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)phi_struct;
	p = phi->philo;
	phi->last_meal = get_time(p);
	while (check_end_condition(phi))
	{
		pthread_mutex_lock(&(p->forks[0]));
		ph_print("has taken a fork", phi->index, p);
		pthread_mutex_lock(&(p->forks[0]));
		while (check_end_condition(phi))
			ph_usleep(0, p);
	}
	return (phi_struct);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	i;

	i = 0;
	str = malloc(count * size);
	if (!str)
		return (NULL);
	while (i < count * size)
		((unsigned char *)str)[i++] = 0;
	return (str);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	b;

	a = 1;
	b = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			a *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		b = 10 * b + (*str - '0');
		str++;
	}
	return (b * a);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}


/* void	*one_philo(void *philosopher_struct)
{
	t_phisolopher	*phi;
	t_philo			*p;

	phi = (t_phisolopher *)philosopher_struct;
	p = phi->philo;
	phi->last_meal = get_time(p);
	pthread_mutex_lock(&(phi->checker_mutex));
	pthread_mutex_lock(&(p->forks[phi->index]));
	ph_print("has taken a fork", phi->index, p);
	pthread_mutex_unlock(&(p->forks[phi->index]));
	pthread_mutex_unlock(&(phi->checker_mutex));
	if (pthread_create(&(phi->th_checker), NULL, &checker, phi))
		ph_error("Failed to create thread", p);
	if (pthread_join(phi->th_checker, NULL))
		ph_error("Failed to join thread", p);
	pthread_detach(p->phi[0].th);
	return (NULL);
} */

/* 	if (p->number_of_philosophers == 1)
	{
		if (pthread_create(&(p->phi[0].th), NULL, &one_philo, &(p->phi[0])))
			ph_error("Failed to create thread", p);
		while (p->death == false)
			ph_usleep(0, p);
		return ;
	} */