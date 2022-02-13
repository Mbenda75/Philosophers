/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:06 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/13 18:04:12 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

long int		actual_time(void)
{
	long int			time;
	struct timeval		current_time;

 	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

int	check_dead(t_utils_philo *philo)
{
    pthread_mutex_lock(&philo->info->death_mutex);
	if ((actual_time() - philo->info->start_time) - philo->last_meal >= philo->info->time_die)
	{
        pthread_mutex_lock(&philo->info->stop_mutex);
        philo->info->stop = 1;
        pthread_mutex_unlock(&philo->info->stop_mutex);
		display_msg(philo, DEAD, 1);
        pthread_mutex_unlock(&philo->info->death_mutex);
		return  (0);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (1);
}
int check_stop(t_utils_arg *info)
{
    int ret;
    pthread_mutex_lock(&info->stop_mutex);
    ret = info->stop; 
    pthread_mutex_unlock(&info->stop_mutex);
    return (ret);
}

int     check_eat(t_utils_philo *philo)
{
    pthread_mutex_lock(&philo->info->eat_mutex);
    if (philo->info->finish_eat == philo->info->nb_eat && philo->info->nb_eat != 0)
    {
        pthread_mutex_lock(&philo->info->stop_mutex);
        philo->info->stop = 1;
        pthread_mutex_unlock(&philo->info->stop_mutex);
		display_msg(philo, ALL, 1);
        pthread_mutex_unlock(&philo->info->eat_mutex);
        return  (0);
    }
    pthread_mutex_unlock(&philo->info->eat_mutex);
    return (1);
}
int main (int ac, char **av)
{
    if (ac > 6 || ac < 5)
        return (1);
    t_utils_philo *philo;
    t_utils_arg info;
    check_arg(av);
    philo = malloc(sizeof(t_utils_philo) * ft_atoi(av[1]));
    philo = file_struc(philo, &info, av);
    start_philo(philo);
    free(philo);
    return (0);
}