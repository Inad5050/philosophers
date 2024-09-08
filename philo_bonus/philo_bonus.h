/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:03:59 by dani              #+#    #+#             */
/*   Updated: 2024/09/09 00:08:46 by dani             ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h> 
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define LOCK   1
# define UNLOCK 0

typedef struct s_philo	t_philo;

typedef struct s_philosopher
{
	int				index;
	long			last_meal;
	int				times_eaten;
	pthread_t		th_checker;
	char			*checker_sem_name;
	sem_t			*checker_sem;
	bool			checker_sem_created;
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
void	ph_print(char *str, int i, t_philo *p);
void	ft_usleep(long time, t_philo *p);

//checker
void	*checker(void *philosopher_struct);
void	check_death(t_phisolopher *phi);
void	check_max_meals(t_phisolopher *phi);

//exit
void	ph_error(char *str, t_philo *p);
void	free_memory(t_philo *p);

//libft
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
char	*ph_strjoin(char *s1, char c);

//parsing
int		parsing(t_philo	*p, int argc, char **argv);
int		check_args(t_philo	*p, char **argv);
int		initiate_args(t_philo *p, int argc, char **argv);
int		initiate_struct_phi(t_philo	*p);
int		initiate_sems(t_philo	*p);

//philo
void	start_process(t_philo *p);
void	routine(t_phisolopher *phi);
void	forks(t_phisolopher *phi, int i);
void	philo_eat(t_phisolopher *phi);

#endif

/* 
if (phi->index == 0)
	printf("(DEAD get_time - phi[%i]->last_meal) == result\
>= p->time_to_die %lu %lu %lu %lu\n", phi->index, time, \
phi->last_meal, time - phi->last_meal, p->time_to_die);
*/


/* APUNTES
Diferencias clave entre sem_open y sem_init:
Contexto de uso:

sem_open: Se utiliza para trabajar con semaforos nombrados que pueden 
ser compartidos entre diferentes procesos. Estos semáforos se identifican 
mediante un nombre global (como un archivo) y están disponibles en 
todo el sistema para cualquier proceso que conozca su nombre.

sem_init: Se utiliza para inicializar semaforos no nombrados 
(también llamados semaforos anónimos) que se pueden compartir solo 
entre hilos de un mismo proceso o entre procesos que comparten la misma 
memoria. Estos semáforos no tienen un nombre global y solo son accesibles 
dentro de la memoria compartida por los procesos o hilos. */

/* Vida útil

sem_open: Los semáforos creados con sem_open pueden persistir más allá 
de la vida útil del proceso, y son gestionados como objetos del sistema 
(similar a archivos). Para eliminar un semáforo nombrado, se utiliza la 
función sem_unlink.

sem_init: Los semáforos inicializados con sem_init existen solo dentro 
del proceso o memoria compartida en la que fueron creados, y su vida útil 
está vinculada a esa memoria. */


/* Cierre

sem_close: Libera los recursos asociados con el semáforo dentro del 
proceso actual, es decir, desconecta el semáforo en ese proceso. 
Esto no elimina el semáforo del sistema; solo cierra su referencia en 
ese proceso específico.

sem_unlink: Elimina el nombre del semáforo del sistema, pero el 
semáforo sigue existiendo mientras haya procesos que aún lo tengan 
abierto. Una vez que todos los procesos cierran el semáforo con 
sem_close, el semáforo se destruye automáticamente y se liberan 
todos los recursos asociados. */


/* Sem_unlink no libera los recursos utilizados 
directamente por el semáforo, sino que elimina el nombre del semáforo 
del sistema de archivos, haciendo que ya no sea accesible por su nombre. 
Sin embargo, el semáforo sigue existiendo en memoria y puede ser utilizado 
hasta que todos los procesos que lo están usando lo cierren mediante 
sem_close.

Explicación detallada:
sem_close: Libera los recursos asociados con el semáforo dentro del 
proceso actual, es decir, desconecta el semáforo en ese proceso. 
Esto no elimina el semáforo del sistema; solo cierra su referencia 
en ese proceso específico.

sem_unlink: Elimina el nombre del semáforo del sistema, pero el semáforo 
sigue existiendo mientras haya procesos que aún lo tengan abierto. 
Una vez que todos los procesos cierran el semáforo con sem_close, 
el semáforo se destruye automáticamente y se liberan todos los recursos 
asociados. */


/* Flujo de uso:

Abrir/crear el semáforo: Se usa sem_open para abrir o crear un semáforo 
nombrado. Este semáforo puede ser compartido entre múltiples procesos.

Usar el semáforo: Los procesos sincronizan el acceso a la sección crítica 
usando sem_wait y sem_post.

Cerrar el semáforo (sem_close): Cada proceso debe llamar a sem_close 
cuando ya no necesita usar el semáforo, liberando los recursos del semáforo 
en ese proceso.

Eliminar el semáforo del sistema (sem_unlink): Una vez que el semáforo 
ya no es necesario, un proceso debe llamar a sem_unlink para eliminar 
su nombre del sistema. Esto asegura que otros procesos ya no puedan abrir 
o crear el semáforo con el mismo nombre.

Recursos liberados automáticamente: Aunque el nombre del semáforo se 
haya eliminado con sem_unlink, el semáforo seguirá existiendo mientras 
haya procesos que lo hayan abierto. Los recursos del semáforo se liberan 
automáticamente cuando todos los procesos que lo usaban lo cierran con 
sem_close. */

/* 
SEM_OPEN

sem_t *sem_open(const char *name, int oflag, ...);
Parámetros:
name: Un puntero a una cadena de caracteres que representa el nombre 
del semáforo. Este debe comenzar con un /, como en "/miSemaforo".

oflag: Especifica cómo se abrirá el semáforo. Las opciones comunes son:

O_CREAT: Crea un nuevo semáforo si no existe.
O_EXCL: Si se utiliza junto con O_CREAT, hace que la llamada falle 
si el semáforo ya existe.
modo (opcional): Si se usa O_CREAT, también se debe proporcionar este 
parámetro para especificar los permisos del semáforo 
(por ejemplo, S_IRUSR | S_IWUSR para lectura/escritura por el propietario).

value (opcional): Si se usa O_CREAT, también se debe proporcionar un 
valor inicial para el semáforo (por ejemplo, 1 para un semáforo binario). 
*/