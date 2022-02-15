/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:11:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/15 20:02:03 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_utils_arg	*init_struc(t_utils_arg *info, char **av)
{
	info->nb_philo = ft_atol(av[1]);
	info->time_die = ft_atol(av[2]);
	info->time_eat = ft_atol(av[3]);
	info->time_sleep = ft_atol(av[4]);
	if (av[5])
		info->nb_eat = ft_atol(av[5]);
	else
		info->nb_eat = 0;
	info->start_time = 0;
	info->finish_eat = 0;
	info->stop = 0;
	return (info);
}

t_utils_philo	*file_struc(t_utils_philo *philo, t_utils_arg *info, char **av)
{
	pthread_t	*thread;
	int			i;
	int			nb;

	i = -1;
	nb = ft_atol(av[1]);
	thread = malloc(sizeof(pthread_t) * nb);
	while (++i < nb)
	{
		philo[i].info = init_struc(info, av);
		philo[i].thread = thread[i];
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].to_eat = 0;
		pthread_mutex_init(&philo[i].left_fork, NULL);
		if (i == nb - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
	}
	free(thread);
	return (philo);
}
