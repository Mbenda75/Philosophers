/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/01/29 14:00:12 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_THREADS 5

pthread_mutex_t     mutex;

void    *routine_eat()
{
    //pthread_mutex_lock(&mutex);
    printf("Philo is eating\n");
    //pthread_mutex_unlock(&mutex);
}

int main(int ac, char **av)
{
    (void)ac;
    int i = 0;
    int nb = atoi(av[1]);
    pthread_t thread[nb];
  

    //pthread_mutex_init(&mutex, NULL);
    while (i < nb)
    {
        
        pthread_create(&thread[i], NULL, &routine_eat, NULL); //Creation du thread
        i++;
    }
    i = 0;
    while (i < nb)
    { 
        pthread_join(thread[i], NULL);   //Permet de suspendre lexecution dun thread le temps
                                        //qu un autre finisse equivaut a WAITPID
        i++;
    }
    //pthread_mutex_destroy(&mutex);
    return (0);
}