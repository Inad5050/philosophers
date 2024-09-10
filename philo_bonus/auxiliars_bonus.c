/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:36:42 by dani              #+#    #+#             */
/*   Updated: 2024/09/10 12:02:48 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(t_philo *p)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ph_error("Couldn't get_time", p), 0);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

void	ph_print(char *str, int i, t_philo *p)
{
	sem_wait(p->write_sem);
	if (p->death == false && p->max_meals == false)
		printf("%lu %i %s\n", get_time(p) - p->initial_time, i + 1, str);
	sem_post(p->write_sem);
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