#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_utils_arg
{
    int     nb_philo;
    int     time_die; // s’il a pas mangé depuis time_to_die millisecondes il meurt
    int     time_eat; //temps pour manger avec deux fourchettes en millisecondes
    int     time_sleep; //temps pour dormir en milliseconde
    int     nb_eat; /// nb de fois qu un philo doit manger
    int     id;          //index pour boucler sur le nombre de philo
    //int     stock_time;
   // int     lock;
}   t_utils_arg;


typedef struct s_utils_philo
{
    struct s_utils_arg info;
    pthread_t   *thread;
    pthread_mutex_t     left_fork;
    pthread_mutex_t     sleep_mutex;
    pthread_mutex_t     *right_fork;
}   t_utils_philo;

void    for_sleep(t_utils_philo *th)
{
    printf("\033[96mPhilo %d is sleeping\033[0m\n", th->info.id);
    //usleep(th->info.time_sleep);
}

void    for_eat(t_utils_philo *th)
{
    struct timeval time;
    if (th->info.id != th->info.nb_philo)
    {
        gettimeofday(&time, NULL);
        printf("[Time START is %ld\n", time.tv_usec);
    }
    if (th->info.id < th->info.nb_philo)
    {
        //pthread_mutex_lock(th->info->right_fork);
        th->info.id++;
        printf("\033[95mPhilo %d is eating\033[0m\n", th->info.id);
        //pthread_mutex_unlock(th->info->right_fork);
    }
    else
        exit(1);
    gettimeofday(&time, NULL);
    printf("Time END is %ld]\n", time.tv_usec);
    //usleep(th->info.time_eat);
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

void    init_struc(t_utils_arg *th, char **av)
{
    th->nb_philo = atoi(av[1]);
    th->time_die = atoi(av[2]);
    th->time_eat = atoi(av[3]);
    th->time_sleep = atoi(av[4]);
    //th->nb_eat = atoi(av[5]);
    th->id = 0;
}


int main (int ac, char **av)
{
    t_utils_philo philo;
    t_utils_arg info;

    init_struc(&info, av);

    pthread_t *thread = malloc(sizeof(pthread_t) * info.nb_philo);
    pthread_mutex_init(&philo.sleep_mutex, NULL);
    pthread_mutex_init(&philo.left_fork, NULL);
    int j =0;
    philo.thread = thread;
    while(j < info.nb_philo)
    {
        pthread_create(&philo.thread[j], NULL, &routine, &info);
        //sleep(2);
        j++;
    }
    j = 0;
    while (j < info.nb_philo)
    {
        pthread_join(philo.thread[j], NULL);
        //sleep(2);
        j++;
    }
    pthread_mutex_destroy(&philo.left_fork);
    pthread_mutex_destroy(&philo.sleep_mutex); 
    return (0);
}

/*
    printf("Time is %ld\n", time.tv_usec);
     printf("t_sleep == %d\n", info.time_sleep);
    printf("t_eat == %d\n", info.time_eat);
    printf("t_die == %d\n", info.time_die);
    printf("nb philo == %d\n", info.nb_philo); */