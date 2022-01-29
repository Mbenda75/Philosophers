/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:35:28 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/29 14:28:33 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_THREADS 5

///Mutex === fourchette
//Mutex_lock == bloque la fourchette pour aucun thread la prenne
//Mutex_unlock == va me permettre de liberer la fourchette pour un autre thread
//if NB_THREAD est un nb pair faire manger la moitier de NB_THREAD pendant que les autres dorment
//if NB_TRHEAD est un nb impair n thread vont manger pendant que n/2 + 1 thread dormiront
//Faire un tableau de thread et mettre mes different thread dedans 
//faire un tableau de mutext 
//Faire une structure avec toute mes variables times_to et mes Right&Left fourchette
//

pthread_mutex_t     mutex;
int i = 0;

void    *routine()
{
    pthread_mutex_lock(&mutex);
    i = i + 2;
    printf("routine i == %d\n", i);

    i = i + 2;
      printf("routine2 i == %d\n", i);
    pthread_mutex_unlock(&mutex);
}

int main(int ac, char **av)
{
    (void)ac;
    int i = 0;
    pthread_t thread[NB_THREADS];
  

    pthread_mutex_init(&mutex, NULL);
    while (i < NB_THREADS)
    {
        
        pthread_create(&thread[i], NULL, &routine, NULL); //Creation du thread
       
        i++;
    }
    i = 0;
    while (i < NB_THREADS)
    {
       
        pthread_join(thread[i], NULL);   //Permet de suspendre lexecution dun thread le temps
                                        //qu un autre finisse equivaut a WAITPID
       
        i++;
    }
    return (0);
}