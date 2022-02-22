#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_main		t_main;

typedef struct s_philo
{
	int	time;
	int	left_fork;
	int	right_fork;
	int n_philo;
	long int	last_meal;
	pthread_mutex_t	mutex;
	pthread_t 		thread;
	t_main		*st_main;
}		t_philo;

struct s_main
{
	int	numb_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int numb_meal;
	t_philo	*philo;
};

int			ft_error(void);
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
long int	get_time(void);
int		died(t_philo *philo);

#endif