#include "../include/philo.h"

int main(int ac, char **av)
{
    t_data *data;
    int i;

    i = 0;
    if (parse_args(ac, av, data) != 0)
        return(1);
    if (initiate_philo(data) != 0)
        return(1);
    if(link_thread(data))
        return(1);
    free_all(data);
    return(0);
}
