#include "../include/philo.h"

int is_digit(char **av, int ac)
{
    int i;
    int j;

    j = 1;
    while(j < ac)
    {
        i = 0;
        if(av[j][0] == '\0')
            return(0);
        while(av[j][i])
        {
            if(av[j][i] < '0' || av[j][i] > '9')
                return(0);
            i++;
        }
        j++;
    }
    return(1);
}

int philo_atoi(char *str)
{
    int result;
    int i;
    int before;

    result = 0;
    before = 0;
    i = 0;
    while(str[i] >= '0' && str[i] <= '9')
    {
        before = result;
        result *= 10;
        result += str[i] - '0';
        if(before > result)
            return(-2);
        i++;
    }
    return(result);
}