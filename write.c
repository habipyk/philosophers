#include "philo.h"

void	ft_write(int action, t_philo *ph, char *str, t_time time)
{
	pthread_mutex_lock(ph->data->death);
	if (ph->data->corpse == 0)
	{
		if (action == 1)
			printf("%llu %d %s\n", time, ph->id + 1, str);
		else
			printf("%llu %d is %s\n", time, ph->id + 1, str);
	}
	pthread_mutex_unlock(ph->data->death);
}
