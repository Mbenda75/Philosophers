/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:19:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/09 19:04:36 by benmoham         ###   ########.fr       */
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
    long int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    long int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    long int     time_sleep; //temps pour dormir en milliseconde
    int     nb_eat; /// nb de fois qu un philo doit manger
   
    long int     start_time;
    //int fork_lok ;
}   t_utils_arg;


typedef struct s_utils_philo
{
    struct s_utils_arg *info;
    
    int     id;          //id du thread qui sexecute
    long int     last_meal; // temps du dernier repas 

    pthread_t           thread;
    //pthread_t           die_thread;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     sleep_mutex;
    pthread_mutex_t     write_mutex;
    pthread_mutex_t     *right_fork;
}   t_utils_philo;

void    for_sleep(t_utils_philo *philo);
long int		actual_time(void);
void    for_eat(t_utils_philo *philo);
void    for_fork(t_utils_philo *philo);
void    *routine(void *arg);
void    check_arg(char **av);
void    exec_philo(t_utils_philo *philo);
int	    ft_isdigit(char s);
int     ft_atoi(const char *str);
void	ft_usleep(long int time_in_ms);
void    start_philo(t_utils_philo *philo);
t_utils_arg     *init_struc(t_utils_arg *th, char **av);
t_utils_philo   *file_struc(t_utils_philo *philo, t_utils_arg *info ,char **av);
#endif