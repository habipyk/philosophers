#include "philo.h"

void	ft_exit(char *str)
{
	printf("%s", str);
	exit(1);
}

void	structinit(t_data *data, int ac, char *av[])
{
	int	i;

	i = 0;
	data->philo_n = ft_atoi(av[1]);
	data->death_timer = ft_atoi(av[2]);
	data->meal_timer = ft_atoi(av[3]);
	data->sleep_timer = ft_atoi(av[4]);
	data->corpse = 0;
	data->ac = ac;
	data->av = av;
	if (data->philo_n <= 0 || data->death_timer <= 0 || data->sleep_timer <= 0
		|| data->sleep_timer <= 0 || data->meal_timer <= 0)
		ft_exit("Check arguments\n");
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (data->philo == 0)
		ft_exit("Allocation failed\n");
}

void	philoinit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].timer = ft_get_time();
		data->philo[i].last_meal = ft_get_time();
		if (data->ac == 6)
			data->philo->round = ft_atoi(data->av[5]);
		if (data->ac == 6 && data->philo->round <= 0)
			ft_exit("Check arguments\n");
		i++;
	}
}

void	mutexinit(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (data->forks == 0 || data->death == 0)
		ft_exit("Allocation failed\n");
	while (i < data->philo_n)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->death, NULL);
}

void	ft_lastmeal(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->data->death);
}

void	nietzsche(t_philo *phi)
{
	if (phi->data->philo_n == 1)
	{
		ft_sleep_time(phi, phi->data->death_timer);
		phi->data->corpse = 1;
	}
}

void	*simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&ph->data->forks[ph->id]);
		ft_write(1, ph, "has taken a fork", ft_get_time() - ph->timer);
		nietzsche(ph);
		pthread_mutex_lock(&ph->data->forks[(ph->id + 1)
			% (ph->data->philo_n)]);
		ft_write(1, ph, "has taken a fork", ft_get_time() - ph->timer);
		ft_write(2, ph, "eating", ft_get_time() - ph->timer);
		checker(ph, 1);
		ft_sleep_time(ph, ph->data->meal_timer);
		checker(ph, 2);
		ft_lastmeal(ph);
		pthread_mutex_unlock(&ph->data->forks[ph->id]);
		pthread_mutex_unlock(&ph->data->forks[(ph->id + 1)
			% (ph->data->philo_n)]);
		ft_write(2, ph, "sleeping", ft_get_time() - ph->timer);
		ft_sleep_time(ph, ph->data->sleep_timer);
		ft_write(2, ph, "thinking", ft_get_time() - ph->timer);
	}
	return (0);
}

void	start_simulation(t_data *data)
{
	int		i;
	t_time	time;

	i = 0;
	while (i < data->philo_n)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &simulation,
				&data->philo[i]))
		{
			ft_exit("Creating thread->failed.\n");
		}
		i++;
		usleep(100);
	}
	i = 0;
	while (1)
	{
		pthread_mutex_lock(data->death);
		time = ft_get_time() - data->philo->last_meal;
		i = ft_death_check(data->philo, time);
		if (i != -1)
			break ;
		// else if (data->ac == 6 && ft_stomach_check(data->philo, time))
		//	break ;
		pthread_mutex_unlock(data->death);
	}
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == 0)
		ft_exit("Allocation failed\n");
	if (ac == 5 || ac == 6)
	{
		structinit(data, ac, av);
		philoinit(data);
		mutexinit(data);
		start_simulation(data);
	}
	else
		ft_exit("Check arguments\n");
}
