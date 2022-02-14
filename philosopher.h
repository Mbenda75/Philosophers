/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:19:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/13 17:09:24 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define FORK       "has taken a fork\n"
# define EAT        "is eating\n"
# define SLEEP      "is sleeping\n"
# define THINK      "is thinking\n"
# define DEAD       "is dead\n"
# define ALL        "all philo have eaten\n"

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_utils_arg
{
    int     nb_philo;
    long int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    long int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    long int     time_sleep; //temps pour dormir en milliseconde
    int     nb_eat; /// nb de fois qu un philo doit manger
    pthread_mutex_t     write_mutex;
    pthread_mutex_t     death_mutex;
    pthread_mutex_t     eat_mutex;
    pthread_mutex_t     stop_mutex;
    long int     start_time;
    int         finish_eat;
    int         stop;
}   t_utils_arg;


typedef struct s_utils_philo
{
    struct s_utils_arg *info;
    
    int        id;          //id du thread qui sexecute
    long int     last_meal; // temps du dernier repas 
    int         to_eat; // 1 si il a manger sinon 0
    pthread_t           thread;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     *right_fork;
}   t_utils_philo;

long int		actual_time(void);
void    for_eat(t_utils_philo *philo);
void    *routine(void *arg);
int     check_dead(t_utils_philo *philo);
int     check_stop(t_utils_arg *info);
int ft_strlen(char *str);
int   check_arg(char **av);
int	check_max(char *av);
int     check_eat(t_utils_philo *philo);
void    finish_prog(t_utils_philo *philo);
void	take_right_fork(int nb, t_utils_philo *philo);
int	    ft_isdigit(char s);
long    ft_atol(char *str);
void	take_fork(t_utils_philo *philo);
void	ft_usleep(long int time_in_ms, t_utils_arg *info);
void    start_philo(t_utils_philo *philo);
void    display_msg(t_utils_philo *philo, char *msg, int check_die);
t_utils_arg     *init_struc(t_utils_arg *th, char **av);
t_utils_philo   *file_struc(t_utils_philo *philo, t_utils_arg *info ,char **av);
#endif