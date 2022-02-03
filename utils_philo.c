/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/03 18:30:50 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//# define FORK       "has taken a fork"
//# define EAT        "is eating"
//# define SLEEP      "is sleeping"
//# define THINK      "is thinking"
//# define DEAD       "is dead"


typedef struct s_utils_philo
{
    int     nb_philo;
    int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    int     time_sleep; //temps pour dormir en milliseconde
    
    //pthread_mutex_t     fork_left;
    //pthread_mutex_t     *right_left;
        
}   t_utils_philo;

void   init_struc(t_utils_philo *th, char **av)
{
    th->nb_philo = atoi(av[1]);
    th->time_die = atoi(av[2]);
    th->time_eat = atoi(av[3]);
    th->time_sleep = atoi(av[4]);
}

pthread_mutex_t     mutex;

void    *routine_eat()
{
    pthread_mutex_lock(&mutex);
    printf("Philo is eating\n");
    pthread_mutex_unlock(&mutex);
}

int	ft_isdigit(char s)
{
	if (s >= '0' && s <= '9')
		return (0);
	else
		return (1);
}

void    check_arg(char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(av[i])
    {
        while (av[i][j])
        {
            if (ft_isdigit(av[i][j]) == 1 || atoi(av[1]) > 200)
            {
                printf("bad character\n");
                exit(1);
            }
            j++;
        }
        j = 0;
        i++;
    }
}

int main(int ac, char **av)
{
    (void)ac;
    int i = 0;
    t_utils_philo th;
    
    init_struc(&th, av);
    pthread_t thread[th.nb_philo];
  
    pthread_mutex_init(&mutex, NULL);
    check_arg(av);
    while (i < th.nb_philo)
    {
        pthread_create(&thread[i], NULL, &routine_eat, NULL);
        i++;
    }
    i = 0;
    while (i < th.nb_philo)
    { 
        pthread_join(thread[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&mutex); 
    return (0);
}