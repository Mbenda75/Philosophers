#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_utils_philo
{
    int     nb_philo;
    int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    int     time_sleep; //temps pour dormir en milliseconde
    
    pthread_mutex_t     left_fork;
    pthread_mutex_t     *right_fork;
}   t_utils_philo;

int i = 0;

void    *routine_eat(void *fork)
{
    t_utils_philo *fork2;

    fork2 = (t_utils_philo *)fork;

  /*   pthread_mutex_lock(fork2->left_fork);
    pthread_mutex_lock(fork2->right_fork); */
    struct timeval time;
  
    while (1)
    {
        if (i != fork2->nb_philo)
        {
            gettimeofday(&time, NULL);
            printf("Time is %ld\n", time.tv_usec);
        }

        if (i != fork2->nb_philo)
        {
            pthread_mutex_lock(&fork2->left_fork);
            //pthread_mutex_lock(fork2->right_fork);
            i++;
            printf("Philo %d is eating\n", i);

            printf("Philo %d has finished to eat\n", i);
            pthread_mutex_unlock(&fork2->left_fork);
            //pthread_mutex_unlock(fork2->right_fork);
        }
        else
            exit(1);
        
        gettimeofday(&time, NULL);
        printf("Time is %ld\n", time.tv_usec);
    }

}

void   init_struc(t_utils_philo *th, char **av)
{
    th->nb_philo = atoi(av[1]);
    //th->time_die = atoi(av[2]);
    //th->time_eat = atoi(av[3]);
    //th->time_sleep = atoi(av[4]);
}

int main (int ac, char **av)
{
    t_utils_philo philo;

    init_struc(&philo, av);

    pthread_t t[philo.nb_philo];
    pthread_mutex_init(&philo.left_fork, NULL);
    int j =0;

    while(j < philo.nb_philo)
    {
       pthread_create(&t[j], NULL, &routine_eat, &philo);
        j++;
    }
    j = 0;
    while (j < philo.nb_philo)
    {
        pthread_join(t[j], NULL);
        j++;
    }
    return (0);
}

/* 
    printf("Time is %ld\n", time.tv_usec);
    printf("t_sleep == %d\n", fork2->time_sleep);
    printf("t_eat == %d\n", fork2->time_eat);
    printf("t_die == %d\n", fork2->time_die);
    printf("nb philo == %d\n", fork2->nb_philo); */