/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:05:45 by dani              #+#    #+#             */
/*   Updated: 2024/09/03 17:13:11 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//get p->current_time in microseconds
unsigned long	get_time(t_philo *p)
{
	struct 			timeval	*tv;
	unsigned long	current_time;
	
	tv = ft_calloc(1, sizeof(struct timeval));
	if (gettimeofday(tv, NULL))
	{
		free(tv);
		return (ph_error("Couldn't get_time", p), 0);
	}
	current_time = tv->tv_usec;
	return (free(tv), current_time);
}

//NECESITA MUTEX?
void	ph_print(char *str, int i, t_philo *p)
{
	unsigned long	current_time;
	
	current_time = get_time(p);
	printf("%lu %i %s\n", current_time - p->initial_time, i, str);
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
