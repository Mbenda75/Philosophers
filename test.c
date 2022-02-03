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
    int     i;          //index pour boucler sur le nombre de philo
    int     stock_time;
    int     lock;

    pthread_mutex_t     left_fork;
    pthread_mutex_t     sleep_mutex;
    pthread_mutex_t     *right_fork;
    
}   t_utils_philo;

void    for_sleep(t_utils_philo *th)
{
    printf("\033[96mPhilo %d is sleeping\033[0m\n", th->i);
    usleep(th->time_sleep);
}
void    for_eat(t_utils_philo *th)
{
    struct timeval time;
    if (th->i != th->nb_philo)
    {
        gettimeofday(&time, NULL);
        printf("[Time START is %ld\n", time.tv_usec);
    }
    if (th->i < th->nb_philo)
    {
        //pthread_mutex_lock(th->right_fork);
        th->i++;
        printf("\033[95mPhilo %d is eating\033[0m\n", th->i);
        printf("\033[93mPhilo %d has finished to eat\033[0m\n", th->i);
        //pthread_mutex_unlock(th->right_fork);
    }
    else
        exit(1);
    gettimeofday(&time, NULL);
    printf("Time END is %ld]\n", time.tv_usec);
    usleep(th->time_eat);
}

void    *routine(void *philo)
{
    t_utils_philo *th;

    th = (t_utils_philo *)philo;
    while (1)
    {
        pthread_mutex_lock(&th->left_fork);
        for_eat(th);
        pthread_mutex_unlock(&th->left_fork);
        pthread_mutex_lock(&th->sleep_mutex);
        for_sleep(th);
        pthread_mutex_unlock(&th->sleep_mutex);

    }
}

void   init_struc(t_utils_philo *th, char **av)
{
    th->nb_philo = atoi(av[1]);
    th->time_die = atoi(av[2]);
    th->time_eat = atoi(av[3]);
    th->time_sleep = atoi(av[4]);
    th->i = 0;
    th->lock = 0;
}

int main (int ac, char **av)
{
    t_utils_philo philo;

    init_struc(&philo, av);

    pthread_t t[philo.nb_philo];
    pthread_mutex_init(&philo.left_fork, NULL);
    pthread_mutex_init(&philo.sleep_mutex, NULL);
    //pthread_mutex_init(philo.right_fork, NULL);
    int j =0;

    while(j < philo.nb_philo)
    {
        pthread_create(&t[j], NULL, &routine, &philo);
        //sleep(2);
        j++;
    }
    j = 0;
    while (j < philo.nb_philo)
    {
        pthread_join(t[j], NULL);
        //sleep(2);
        j++;
    }
    pthread_mutex_destroy(&philo.left_fork);
    pthread_mutex_destroy(&philo.sleep_mutex);
    return (0);
}

/*
    printf("Time is %ld\n", time.tv_usec);
    printf("t_sleep == %d\n", fork2->time_sleep);
    printf("t_eat == %d\n", fork2->time_eat);
    printf("t_die == %d\n", fork2->time_die);
    printf("nb philo == %d\n", fork2->nb_philo); */