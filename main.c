/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:06 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/09 19:22:54 by benmoham         ###   ########.fr       */
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
		exit(-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

int main (int ac, char **av)
{
    if (ac > 6 || ac < 5)
        exit(1);
    t_utils_philo *philo;
    t_utils_arg info;
    check_arg(av);
    philo = malloc(sizeof(t_utils_philo) * ft_atoi(av[1]));
    philo = file_struc(philo, &info, av);
    start_philo(philo);
    return (0);
}