/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/10 21:11:19 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    *routine(void *arg)
{
    t_utils_philo *philo;
    
    philo = (t_utils_philo *)arg;
    usleep(50);
    while (check_dead(philo))
    {   
        if (!philo->id % 2)
            usleep (50);  
        for_eat(philo);
        display_msg(philo, SLEEP, 0);
        ft_usleep(philo->info->time_sleep);
        display_msg(philo, THINK, 0);
        usleep(50);
    }
    return (NULL);
} 
void    create_thread(t_utils_philo *philo)
{
    int j;
    j = 0;
    while(j <  philo->info->nb_philo)
    {
        pthread_create(&philo[j].thread, NULL, &routine, &philo[j]);
        j++;
    }
    while (1)
    {
        j = -1;
        while (++j < philo->info->nb_philo)
        {
            if (!check_dead(&philo[j]))
            {
                j = 0;
                while(j < philo->info->nb_philo)
                {
                    pthread_join(philo[j].thread, NULL);
                    j++;
                }
                j = -1;
                while(++j < philo->info->nb_philo)
                    pthread_mutex_destroy(&philo[j].left_fork);
               pthread_mutex_destroy(&philo->info->death_mutex);
               pthread_mutex_destroy(&philo->info->write_mutex);
               return ;
            }
        }
        usleep(50);
    }
    j = 0;
    while(j < philo[j].info->nb_philo)
    {
        pthread_join(philo[j].thread, NULL);
        j++;
    }
}


void    start_philo(t_utils_philo *philo)
{
    int j;
    
    philo->info->start_time = actual_time();
    j = 0;
    pthread_mutex_init(&philo->info->write_mutex, NULL);
    pthread_mutex_init(&philo->info->death_mutex, NULL);
    create_thread(philo);

    while(++j < philo->info->nb_philo)
        pthread_mutex_destroy(&philo[j].left_fork);
        
    pthread_mutex_destroy(&philo->info->write_mutex);
}
