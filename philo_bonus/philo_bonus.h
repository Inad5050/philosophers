/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:03:59 by dani              #+#    #+#             */
/*   Updated: 2024/09/12 20:42:26 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>

# define LOCK   1
# define UNLOCK 0

typedef struct s_philo	t_philo;

typedef struct s_philosopher
{
	int				index;
	pid_t			pid;
	long			last_meal;
	int				times_eaten;
	bool			eating;
	bool			end_condition;
	pthread_t		th_checker;
	char			*eat_sem_name;
	sem_t			*eat_sem;
	bool			eat_sem_created;
	char			*end_sem_name;
	sem_t			*end_sem;
	bool			end_sem_created;
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
	sem_t			*forks_sem;
	bool			forks_sem_created;
	sem_t			*write_sem;
	bool			write_sem_created;
	bool			death;
	bool			max_meals;
};

//auxiliars
long	get_time(t_philo *p);
void	ph_print(char *str, t_phisolopher *phi);
void	ph_usleep(long time, t_philo *p);

//checker
void	*checker_routine(void *phi_struct);
void	check_death(t_phisolopher *phi);
void	check_max_meals(t_phisolopher *phi);
int		check_end_condition(t_phisolopher *phi);

//exit
void	ph_error(char *str, t_philo *p);
void	free_memory(t_philo *p);
void	close_semaphores(sem_t *sem, char *sem_name);

//others
void	one_philo(t_philo *p);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
char	*ph_strjoin(char *s1, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

//parsing
int		parsing(t_philo	*p, int argc, char **argv);
int		check_args(t_philo *p, char **argv);
int		initiate_args(t_philo *p, int argc, char **argv);

//semaphores
int		initiate_semaphores(t_philo	*p);
int		initiate_struct_phi(t_philo	*p);
int		create_semaphore(char *str, int nmb, sem_t **sem, t_philo *p);

//threads
void	start_process(t_philo *p);
void	routine(t_phisolopher *phi);
void	philo_eat(t_phisolopher *phi);
void	forks(t_phisolopher *phi, int i);
void	end_process(t_philo *p);

#endif
