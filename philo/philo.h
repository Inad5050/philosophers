/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:03:59 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 17:30:28 by dangonz3         ###   ########.fr       */
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
	bool			eating;
	bool			end_condition;
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
	pthread_t		checker_th;
	t_phisolopher	*phi;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	bool			write_mutex_initialized;
	pthread_mutex_t	eat_mutex;
	bool			eat_mutex_initialized;
	pthread_mutex_t	end_condition_mutex;
	bool			end_condition_mutex_initialized;
};

//auxiliars
long	get_time(t_philo *p);
void	ph_print(char *str, int i, t_philo *p);
void	ph_usleep(long time, t_philo *p);

//checker
void	*checker_routine(void *p_struct);
int		check_death(t_philo *p);
int		check_max_meals(t_philo *p);
void	activate_end_condition(t_philo *p);

//exit
void	ph_error(char *str, t_philo *p);
void	free_memory(t_philo *p);

//others
void	*one_philo(void *philosopher_struct);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

//parsing
int		parsing(t_philo	*p, int argc, char **argv);
int		check_args(t_philo	*p, char **argv);
int		initiate_args(t_philo *p, int argc, char **argv);
int		initiate_struct_phi(t_philo	*p);
int		initiate_forks(t_philo	*p);

//threads
void	start_threads(t_philo *p);
void	*philo_routine(void *phi_struct);
void	philo_eat(t_phisolopher *phi);
void	forks(t_phisolopher *phi, int i);
int		check_end_condition(t_phisolopher *phi);

#endif
