/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:47:31 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/14 16:08:24 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_msg(t_utils_philo *philo, char *msg, int check_die)
{
	static int	die;

	pthread_mutex_lock(&philo->info->write_mutex);
	die = 0;
	if (die == 0)
	{
		if (check_die == 1)
			die = 1;
		if (check_stop(philo->info) != 1)
			printf("%ld %d %s\n",
				actual_time() - philo->info->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->info->write_mutex);
	}
	else
		pthread_mutex_unlock(&philo->info->write_mutex);
}

void	take_fork(t_utils_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		display_msg(philo, FORK, 0);
		pthread_mutex_lock(philo->right_fork);
		display_msg(philo, FORK, 0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		display_msg(philo, FORK, 0);
		pthread_mutex_lock(&philo->left_fork);
		display_msg(philo, FORK, 0);
	}
	for_eat(philo);
}

void	for_eat(t_utils_philo *philo)
{
	pthread_mutex_lock(&philo->info->eat_mutex);
	if (philo->to_eat < philo->info->nb_eat)
		philo->to_eat++;
	if (philo->to_eat == philo->info->nb_eat && philo->info->nb_eat != 0)
		philo->info->finish_eat++;
	pthread_mutex_unlock(&philo->info->eat_mutex);
	display_msg(philo, EAT, 0);
	ft_usleep(philo->info->time_eat);
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->last_meal = actual_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->info->death_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}
