/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:03:59 by dani              #+#    #+#             */
/*   Updated: 2024/09/04 14:35:13 by dani             ###   ########.fr       */
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

typedef struct s_philosopher
{
	int             index;
    pthread_t		th;
	unsigned long	last_meal;
    int             times_eaten;
    t_philo         *philo;
}		t_phisolopher;

typedef struct s_philo
{
	int	            number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
    int             number_of_times_each_philosopher_must_eat;
    unsigned long	initial_time;
	t_phisolopher	*phi;
	pthread_mutex_t	*mutex;
    pthread_mutex_t write_mutex;
    bool			death;
    bool            max_meals;
}		t_philo;

//auxiliars
unsigned long	get_time(t_philo *p);
void	        ph_print(char *str, int i, t_philo *p);
void        	*ft_calloc(size_t count, size_t size);
int             ft_atoi(const char *str);
void	        ft_putstr_fd(char *s, int fd);

//exit
void            ph_error(char *str, t_philo *p);
void            free_memory(t_philo *p);

//parsing
int	            parsing(t_philo	*p, int argc, char **argv);
int	            check_args(t_philo	*p, char **argv);
int	            initiate_args(t_philo *p, int argc, char **argv);
int             initiate_struct_phi(t_philo	*p);
int             initiate_mutex(t_philo	*p);

//philo
void	        threads(t_philo *p);
void*	        routine(void *p_structure);
void            philo_eat(t_phisolopher *p, int i, unsigned long current_time);

//stop
void            stop_condition(t_philo *p);
void            check_death(t_philo *p);
void            check_max_meals(t_philo *p);
void            stop_threads(t_philo *p)

#endif

/* 
Deberás escribir un programa para la parte obligatoria y otro para la parte bonus (Solo
si decides hacer la parte bonus). Ambas tienen que cumplir con las siguientes reglas:
• ¡Las variables globales están prohibidas!
• Tu(s) programa(s) debe(n) aceptar los siguientes argumentos:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: es el número de filósofos, pero también el número
de tenedores.
◦ time_to_die (en milisegundos): si un filósofo no empieza a comer en time_to_die
milisegundos desde el comienzo de su ultima comida o desde el principio de la
simulación, este morirá.
◦ time_to_eat (en milisegundos): es el tiempo que tiene un filósofo para comer.
Durante ese tiempo, tendrá los tenedores ocupados.
◦ time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo para
dormir.
◦ number_of_times_each_philosopher_must_eat (argumento opcional): si todos los filósofos comen al menos number_of_times_each_philosopher_must_eat
veces, la simulación se detendrá. Si no se especifica, la simulación se detendrá
con la muerte de un filósofo.
• Cada filósofo tendrá asignado un número del 1 al number_of_philosophers.
• El filósofo número 1 se sentará al lado del filósofo número number_of_philosophers.
Cualquier otro filósofo número N se sentarán entre el filósofo número N - 1 y el filósofo
número N + 1.
6

Philosophers Nunca pensé que la filosofía llegara a ser tan letal
Los logs de tu programa:
• Cualquier cambio de estado de un filósofo debe tener el siguiente formato:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Reemplaza timestamp_in_ms con la marca de tiempo actual en milisegundos
y X con el numero del filósofo.
• El estado impreso no debe estar roto o alterado por el estado de otros filósofos
• No puedes tener más de 10ms entre la muerte de un filósofo y el momento en el que
imprimes su muerte.
• Te recuerdo, los filósofos deben evitar morir.

Las reglas específicas para la parte obligatoria son:
• Cada filósofo debe ser un hilo.
• Hay un tenedor entre cada filósofo. por lo tanto, si hay varios filósofos, cada filósofo
debe tener un tenedor a su izquierda y otro a su derecha. si solo hay un filósofo,
solo habrá un tenedor en la mesa.
• Para prevenir que los filósofos dupliquen los tenedores, deberás proteger los estados
de los tenedores con un mutex por cada uno de ellos.
 */

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock 
*/

/* 
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[8];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 8; i++) {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
} 
*/

/* 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i;
    for (i = 0; i < 10; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to created thread");
        }
    }
    for (i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    return 0;
} 
*/

/* 
typedef struct s_philo
{
	int mails;
	pthread_mutex_t mutex;
	
}	t_philo; 
*/