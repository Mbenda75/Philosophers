/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:17:16 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/13 17:45:58 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//int gettimeofday(struct timeval *tv, struct timezone *tz);
/*struct timeval {
    time_t      tv_sec;  = secondes 
    suseconds_t tv_usec; = microsecondes 
};*/

long int		actual_time(void)
{
	long int			time;
	struct timeval		current_time;

 	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
 }

int check_stop(t_utils_arg *info)
{
    int ret;
    pthread_mutex_lock(&info->stop_mutex);
    ret = 1; 
    pthread_mutex_unlock(&info->stop_mutex);
    return (ret);
}
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
 
int main()
{
    struct timeval		current_time;

	
	if (gettimeofday(&current_time, NULL) == -1)
     return 0;

     printf("secc === %ld\n", current_time.tv_sec);
     printf(" micro secc == %ld\n", current_time.tv_usec);
}

1644329107 
74578

void	for_die()
{
	
}
