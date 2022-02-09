/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/09 19:28:14 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    *routine(void *arg)
{
    t_utils_philo *philo;
    
    philo = (t_utils_philo *)arg;
    while (1)
    {
            
        for_fork(philo);
            
        for_eat(philo);

        for_sleep(philo);
 
        //for_think(philo);
        //exit(1); 
    }
} 

void    start_philo(t_utils_philo *philo)
{
    int j;
    
    philo->info->start_time = actual_time();
    j = 0;
    printf("Time START PROGRAM %ld\n", actual_time() - philo->info->start_time);
    pthread_mutex_init(&philo->write_mutex, NULL);
    pthread_mutex_init(&philo->sleep_mutex, NULL);
    while(j <  philo->info->nb_philo)
    {
        if (philo->id % 2 == 0)
           ft_usleep(philo->info->time_eat / 10);
        pthread_create(&philo[j].thread, NULL, &routine, &philo[j]);
        j++;
    }
    j = 0;
    while(j < philo[j].info->nb_philo)
    {
        pthread_join(philo[j].thread, NULL);
        j++;
    }
    j  = 0;
    while(j < philo->info->nb_philo)
    {
        pthread_mutex_destroy(&philo[j].left_fork);
        j++;
    }
    pthread_mutex_destroy(&philo->write_mutex);
    pthread_mutex_destroy(&philo->sleep_mutex); 
}
