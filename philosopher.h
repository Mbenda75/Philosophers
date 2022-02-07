/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:19:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/07 19:12:20 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define FORK       "has taken a fork"
# define EAT        "is eating"
# define SLEEP      "is sleeping"
# define THINK      "is thinking"
# define DEAD       "is dead"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_utils_arg
{
    int     nb_philo;
    int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    int     time_sleep; //temps pour dormir en milliseconde
    int     nb_eat; /// nb de fois qu un philo doit manger
    int     id;          //index pour boucler sur le nombre de philo
    //int     start_time;
   //int     lock;
}   t_utils_arg;


typedef struct s_utils_philo
{
    struct s_utils_arg *info;
    pthread_t           thread;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     sleep_mutex;
    pthread_mutex_t     write_mutex;
    pthread_mutex_t     *right_fork;
}   t_utils_philo;

void    for_sleep(t_utils_philo *th);
void    for_eat(t_utils_philo *th);
void    *routine(void *arg);
void    check_arg(char **av);
void    exec_philo(t_utils_philo *philo);
int	    ft_isdigit(char s);
int     ft_atoi(const char *str);
t_utils_arg     *init_struc(t_utils_arg *th, char **av);
t_utils_philo   *file_struc(t_utils_philo *philo, t_utils_arg *info ,char **av);
#endif