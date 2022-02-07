/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/07 19:10:43 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

 void    for_sleep(t_utils_philo *philo)
{
    pthread_mutex_lock(&philo->write_mutex);
    printf("\033[96mPhilo %d %s\033[0m\n", philo->info->id, SLEEP);
    philo->info->id++;
    pthread_mutex_unlock(&philo->write_mutex);
    //usleep(philo->info->time_sleep);
}

void    for_eat(t_utils_philo *philo)
{
    struct timeval time;
    if (philo->info->id <= philo->info->nb_philo)
    {
        gettimeofday(&time, NULL);
        pthread_mutex_lock(&philo->write_mutex);
        //printf("[Time START EAT is %ld\n", time.tv_usec);
        printf("\033[95mTime START EAT %ld Philo %d %s\033[0m\n", time.tv_usec, philo->info->id, EAT);
    }
    //usleep(philo->info->time_eat);
    gettimeofday(&time, NULL);
    printf("\033[95mTime END EAT is %ld\033[0m\n", time.tv_usec);
    pthread_mutex_unlock(&philo->write_mutex);
}

void    *routine(void *arg)
{
    t_utils_philo *philo;
    
    philo = (t_utils_philo *)arg;
    while (1)
    {
        if (philo->info->id <= philo->info->nb_philo)
        {
            pthread_mutex_lock(&philo->write_mutex);
            printf("\033[93mPhilo %d %s\033[0m\n", philo->info->id, FORK);
            printf("\033[93mPhilo %d %s\033[0m\n", philo->info->id, FORK);
            pthread_mutex_unlock(&philo->write_mutex);
            
            pthread_mutex_lock(&philo->left_fork);
            //pthread_mutex_lock(philo->right_fork);
            for_eat(philo);
            pthread_mutex_unlock(&philo->left_fork);
            //pthread_mutex_unlock(philo->right_fork);
            
            pthread_mutex_lock(&philo->sleep_mutex);
            for_sleep(philo);
            pthread_mutex_unlock(&philo->sleep_mutex);
        }
        else
            exit(1);
    }
} 