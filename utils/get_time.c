#include "../include/philo.h"

long long get_time(void)
{
    struct timeval current_time;
    long int       time;

    time = 0;
    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return(time);
}
