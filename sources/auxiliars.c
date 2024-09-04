/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:50:21 by dani              #+#    #+#             */
/*   Updated: 2024/09/04 18:33:03 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(t_philo *p)
{
	struct 			timeval	tv;
	unsigned long	current_time;
	
	if (gettimeofday(&tv, NULL))
		return (ph_error("Couldn't get_time", p), 0);
	current_time = tv.tv_usec - p->initial_time;
	return (current_time);
}

void	ph_print(char *str, int i, t_philo *p)
{
	pthread_mutex_lock(&(p->write_mutex));
	printf("%lu %i %s\n", get_time(p) - p->initial_time, i, str);
	pthread_mutex_unlock(&(p->write_mutex));
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

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
