#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long	t_time;

typedef struct s_philo
{
	int				id;
	int				round;
	t_time			timer;
	t_time			last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				death_timer;
	int				sleep_timer;
	int				philo_n;
	int				corpse;
	int				meal_timer;
	int				ac;
	char			**av;
	t_philo			*philo;
	pthread_mutex_t	*death;
	pthread_mutex_t	*write;
	pthread_mutex_t	*forks;
}	t_data;

int		ft_atoi(const char *str);
void	structinit(t_data *data, int ac, char *av[]);
void	ft_exit(char *str);
void	ft_write(int action, t_philo *ph, char *str, t_time time);
void	ft_sleep_time(t_philo *phi, int ttime);
void	checker(t_philo *philo, int checker);
t_time	ft_get_time(void);
int		ft_death_check(t_philo *phi, t_time time);
void	nietzsche(t_philo *phi);
#endif