#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



void    *routine()
{
    printf("c le debut\n");
    sleep(2);
     printf("c la fin\n");
}

int main ()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL); 
    pthread_join(t2, NULL); 
    return (0);
}