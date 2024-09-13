/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:22:40 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/12 21:19:40 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_philo(t_philo *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ph_error("Cannot fork()", p);
	if (!pid)
	{
		p->phi[0].last_meal = get_time(p);
		if (pthread_create(&(p->phi[0].th_checker), NULL, \
		&checker_routine, &(p->phi[0])))
			ph_error("Failed to create thread", p);
		sem_wait(p->forks_sem);
		ph_print("has taken a fork", &(p->phi[0]));
		sem_post(p->forks_sem);
		while (check_end_condition(&(p->phi[0])))
			ph_usleep(1, p);
		if (pthread_join(p->phi[0].th_checker, NULL))
			ph_error("Failed to join thread", p);
		exit(0);
	}
	wait(NULL);
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

char	*ph_strjoin(char *s1, char c)
{
	int		i;
	char	*result;

	i = 0;
	while (s1[i])
		i++;
	result = ft_calloc(i + 1 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
	return (result);
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
