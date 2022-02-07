/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:06 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/07 19:07:32 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    start_philo(t_utils_philo *philo)
{
    int j;
    struct timeval time;
    
    j = 0;

    pthread_mutex_init(&philo->sleep_mutex, NULL);
    pthread_mutex_init(&philo->write_mutex, NULL);
    gettimeofday(&time, NULL);
    printf("Time START %ld\n", time.tv_usec);
    while(j <  philo->info->nb_philo)
    {
        pthread_create(&philo[j].thread, NULL, &routine, philo);
        //sleep(1);
        j++;
    }
    j = 0;
    while(j < philo[j].info->nb_philo)
    {
        pthread_join(philo[j].thread, NULL);
        j++;
    }
    j = 0;
    while(j < philo[j].info->nb_philo)
    {
        pthread_mutex_destroy(&philo[j].left_fork);
        j++;
    }
    pthread_mutex_destroy(&philo->sleep_mutex); 
    pthread_mutex_destroy(&philo->write_mutex);
}

int main (int ac, char **av)
{
    t_utils_philo *philo;
    t_utils_arg info;

    check_arg(av);
    philo = malloc(sizeof(t_utils_philo) * ft_atoi(av[1]));
    philo = file_struc(philo, &info, av);
    start_philo(philo);
    return (0);
}

/*
    printf("Time is %ld\n", time.tv_usec);
    printf("t_sleep == %d\n", info.time_sleep);
    printf("t_eat == %d\n", info.time_eat);
    printf("t_die == %d\n", info.time_die);
    printf("nb philo == %d\n", info.nb_philo); */