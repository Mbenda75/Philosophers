/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:17:16 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/01 17:22:54 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


//int gettimeofday(struct timeval *tv, struct timezone *tz);
/*struct timeval {
    time_t      tv_sec;  = secondes 
    suseconds_t tv_usec; = microsecondes 
};*/


int main(int ac, char **av)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    printf("Time is %ld", time.tv_usec);
}