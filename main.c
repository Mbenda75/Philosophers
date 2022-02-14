/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:06 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/14 17:23:26 by benmoham         ###   ########.fr       */
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

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	main(int ac, char **av)
{
	t_utils_philo	*philo;
	t_utils_arg		info;
	
	if (ac > 6 || ac < 5)
		return (1);
	if (check_arg(av) == 1)
		return (1);
	philo = malloc(sizeof(t_utils_philo) * ft_atol(av[1]));
	if (!philo)
		return (-1);
	philo = file_struc(philo, &info, av);
	start_philo(philo);
	free(philo);
	return (0);
}
