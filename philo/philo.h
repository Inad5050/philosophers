/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:03:59 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 18:04:41 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define LOCK   1
# define UNLOCK 0

typedef struct s_philo	t_philo;

typedef struct s_philosopher
{
	int				index;
	pthread_t		th;
	long			last_meal;
	int				times_eaten;
	pthread_t		th_checker;
	pthread_mutex_t	checker_mutex;
	bool			checker_mutex_initialized;
	t_philo			*philo;
}		t_phisolopher;

struct s_philo
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long			initial_time;
	t_phisolopher	*phi;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	bool			write_mutex_initialized;
	bool			death;
	bool			max_meals;
};

//auxiliars
long	get_time(t_philo *p);
void	ph_print(char *str, int i, t_philo *p);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);

//checker
void	*checker(void *philosopher_struct);
void	check_death(t_phisolopher *phi);
void	check_max_meals(t_phisolopher *phi);

//exit
void	ph_error(char *str, t_philo *p);
void	free_memory(t_philo *p);

//parsing
int		parsing(t_philo	*p, int argc, char **argv);
int		check_args(t_philo	*p, char **argv);
int		initiate_args(t_philo *p, int argc, char **argv);
int		initiate_struct_phi(t_philo	*p);
int		initiate_forks(t_philo	*p);

//philo
void	start_threads(t_philo *p);
void	*routine(void *philosopher_struct);
void	philo_eat(t_phisolopher *phi);
void	forks(t_phisolopher *phi, int i);
void	*one_philo(void *philosopher_struct);

#endif

/* 
	if (phi->index == 0)
		printf("DEAD get_time - phi[%i]->last_meal) == result >= \
		p->time_to_die %ld %ld %ld %ld\n", phi->index, get_time(p), \
		phi->last_meal, get_time(p) - phi->last_meal, p->time_to_die);
*/
