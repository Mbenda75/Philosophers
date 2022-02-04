/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:35:28 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/04 13:43:20 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_utils_philo
{
    int     nb_philo;
    int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    int     time_sleep; //temps pour dormir en milliseconde
    int     nb_eat; /// nb de fois qu un philo doit manger
    int     i;          //index pour boucler sur le nombre de philo
    int     stock_time;
    int     lock;

    pthread_t           *thread;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     sleep_mutex;
    pthread_mutex_t     *right_fork;
}   t_utils_philo;

void  init_struc(t_utils_philo *th, char **av)
{
    th->nb_philo = atoi(av[1]);
    th->time_die = atoi(av[2]);
    th->time_eat = atoi(av[3]);
    th->time_sleep = atoi(av[4]);
}

void   *routine_eat(void *p)
{
    t_utils_philo *ph;
    
    ph = (t_utils_philo *)p;
    
    pthread_mutex_lock(&ph->left_fork);
    printf("Philo is eating\n");
    pthread_mutex_unlock(&ph->left_fork);
    return (0);
}

int main (int ac, char **av)
{
    t_utils_philo philo;

    init_struc(&philo, av);

    pthread_t *t;
    t = malloc(sizeof(pthread_t) * philo.nb_philo);
    //philo = malloc(sizeof(t_utils_philo) * philo.nb_philo);
    int i =0;
    pthread_mutex_init(&philo.left_fork, NULL);
    while(i < philo.nb_philo)
    {
        pthread_create(&t[i], NULL, &routine_eat, &philo);
        //philo[i].thread = &t[i];
        i++;
    }
    i =0;
    while (i < philo.nb_philo)
    {
        pthread_join(t[i], NULL);
        i++; 
    }
    return (0);
}