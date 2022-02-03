/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:35:28 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/03 12:36:42 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define NB_THREADS 5

pthread_mutex_t     mutex;
int i = 0;

void    *routine()
{
    pthread_mutex_lock(&mutex);
    i = i + 2;
    printf("routine i == %d\n", i);
    pthread_mutex_unlock(&mutex);
}

void    *routine2()
{
    pthread_mutex_lock(&mutex);
    i = i + 2;
    printf("routine2 i == %d\n", i);
    pthread_mutex_unlock(&mutex);
}

int main(int ac, char **av)
{
    (void)ac;
    int i = 0;
    pthread_t t1, t2;
  

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, &routine, NULL); //Creation du thread
    pthread_create(&t2, NULL, &routine2, NULL);

    
    pthread_join(t1, NULL);   //Permet de suspendre lexecution du main thread le temps
    pthread_join(t2, NULL);                     //qu un autre finisse equivaut a WAITPID
 
    return (0);
}