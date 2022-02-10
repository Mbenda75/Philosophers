/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:11:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/10 20:28:53 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_utils_arg    *init_struc(t_utils_arg *info, char **av)
{
    info->nb_philo = ft_atoi(av[1]);
    info->time_die = ft_atoi(av[2]);
    info->time_eat = ft_atoi(av[3]);
    info->time_sleep = ft_atoi(av[4]);
    if (av[5])
        info->nb_eat = ft_atoi(av[5]);
    info->start_time = 0;
    return (info);
}

t_utils_philo *file_struc(t_utils_philo *philo, t_utils_arg *info ,char **av)
{
    int i = -1;
    int nb = ft_atoi(av[1]);
    pthread_t *thread = malloc(sizeof(pthread_t) * nb);
    while (++i < nb)
    {
        philo[i].info = init_struc(info, av);
        philo[i].thread = thread[i];
        philo[i].id = i + 1;
        philo[i].last_meal = 0;
        pthread_mutex_init(&philo[i].left_fork, NULL);
    }
    i = -1;
    while (++i < nb)
    {
        if (i == nb - 1)
            philo[i].right_fork = &philo[0].left_fork;
        else
            philo[i].right_fork = &philo[i + 1].left_fork;
    }
    free(thread);
    return (philo);
}