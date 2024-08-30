/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:02:23 by dani              #+#    #+#             */
/*   Updated: 2024/08/30 22:41:45 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat] */

#include "../includes/philo.h"

int	main(int argc, char** argv)
{
	t_philo	*p;
	
	if (argc != 5 || argc != 6)
		return (printf("Invalid argument number\n"), 0);
	p = ft_calloc(1, sizeof(t_philo));
	if (!p)
		return (printf("Cannot allocate memory for t_philo\n"), 0);
	initiate_struct(p, argc, argv);
	philosophers(p);
	
	return (0);
}

void	initiate_struct(t_philo	*p, int argc, char** argv)
{
	p->number_of_philosophers = argv[1];
	p->time_to_die = argv[2];
	p->time_to_eat = argv[3];
	p->time_to_sleep = argv[4];
	if (argc != 6)
		p->number_of_philosophers = argv[5];
	p->phi = ft_calloc(p->number_of_philosophers, sizeof(t_phisolopher));
	if (!p->phi)
		return (printf("Cannot allocate memory for t_phisolopher\n"), 0);
}

void	philosophers(t_philo *p)
{
	pthread_t th[8];
    int i;
	int x;

	i = -1;
	x = -1;
    pthread_mutex_init(&(p->mutex), NULL);
    while (++i < 8)
	{
        if (pthread_create(&th[i], NULL, &routine, p) != 0) 
            return (perror("Failed to create thread"), 1);
        printf("Thread %d has started\n", i);
    }
	while (++x < 8)
	{
        if (pthread_join(th[x], NULL) != 0) 
            return (perror("Failed to join thread"), 2);
        printf("Thread %d has finished execution\n", x);
    }
    pthread_mutex_destroy(&(((t_philo*)p)->mutex));
    printf("Number of mails: %d\n", ((t_philo*)p)->mails);
    return (0);
}

/* void* routine(void* p) 
{
    int	i;

	i = 0;
	while (i < 100000)
	{
        pthread_mutex_lock(&(((t_philo*)p)->mutex));
        ((t_philo*)p)->mails++;
        pthread_mutex_unlock(&(((t_philo*)p)->mutex));
		i++;
    }
	return (NULL);
}

int main() 
{
    pthread_t th[8];
    int i;
	int x;
	t_philo *p;
	
	p = ft_calloc(1, sizeof(t_philo));
	i = -1;
	x = -1;
    pthread_mutex_init(&(p->mutex), NULL);
    while (++i < 8)
	{
        if (pthread_create(th + i, NULL, &routine, p) != 0) 
            return (perror("Failed to create thread"), 1);
        printf("Thread %d has started\n", i);
    }
	while (++x < 8)
	{
        if (pthread_join(th[x], NULL) != 0) 
            return (perror("Failed to join thread"), 2);
        printf("Thread %d has finished execution\n", x);
    }
    pthread_mutex_destroy(&(((t_philo*)p)->mutex));
    printf("Number of mails: %d\n", ((t_philo*)p)->mails);
    return (0);
} */
