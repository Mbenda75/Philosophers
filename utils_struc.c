/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:11:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/07 18:56:06 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_utils_arg    *init_struc(t_utils_arg *philo, char **av)
{
    philo->nb_philo = ft_atoi(av[1]);
    philo->time_die = ft_atoi(av[2]);
    philo->time_eat = ft_atoi(av[3]);
    philo->time_sleep = ft_atoi(av[4]);
    //philo->nb_eat = ft_atoi(av[5]);
    philo->id = 1;
    return (philo);
}

t_utils_philo *file_struc(t_utils_philo *philo, t_utils_arg *info ,char **av)
{
    int i = 0;
    int nb = atoi(av[1]);
    pthread_t *thread = malloc(sizeof(pthread_t) * nb);
    while (i < nb)
    {
        philo[i].info = init_struc(info, av);
        philo[i].thread = thread[i];
        pthread_mutex_init(&philo[i].left_fork, NULL);
        philo[i].left_fork = philo[i].left_fork;
        if (i < nb - 1)
            philo[i].right_fork = &philo[0].left_fork;
        else
            philo[i].right_fork = &philo[i + 1].left_fork;
        i++;
    }
    free(thread);
    return (philo);
}