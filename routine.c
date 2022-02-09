/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:47:31 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/09 19:22:32 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    for_fork(t_utils_philo *philo)
{
    pthread_mutex_lock(&philo->write_mutex);
    printf("\033[93mPhilo %d %s\033[0m\n", philo->id, FORK);
    printf("\033[93mPhilo %d %s\033[0m\n", philo->id, FORK);
    pthread_mutex_unlock(&philo->write_mutex);
}

void    for_eat(t_utils_philo *philo)
{
    long int tmp = 0;
    pthread_mutex_lock(&philo->left_fork);
    //pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->write_mutex);
    tmp = actual_time();
    philo->last_meal = tmp;
    printf("\033[94mTime START EAT %ld\n Philo %d %s\033[0m\n", tmp - philo->info->start_time, philo->id, EAT);
    pthread_mutex_unlock(&philo->write_mutex);
    ft_usleep(philo->info->time_eat);
    pthread_mutex_unlock(&philo->left_fork);
    //pthread_mutex_unlock(philo->right_fork);
}

/* void    for_think(t_utils_philo *philo);
{
}
 */
void    for_sleep(t_utils_philo *philo)
{
    pthread_mutex_lock(&philo->sleep_mutex);
    pthread_mutex_lock(&philo->write_mutex);
    printf("\033[96mPhilo %d %s\033[0m\n", philo->id, SLEEP);
    pthread_mutex_unlock(&philo->write_mutex);
    ft_usleep(philo->info->time_sleep);
    pthread_mutex_unlock(&philo->sleep_mutex);
}


