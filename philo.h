/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:27:04 by coder             #+#    #+#             */
/*   Updated: 2022/03/05 00:30:50 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_main		t_main;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				n_philo;
	int				n_meals;
	long int		last_meal;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	t_main			*st_main;
}				t_philo;

struct s_main
{
	int				numb_philos;
	int				time_die;
	int				time_eat;
	int				checker;
	int				time_sleep;
	int				numb_meal;
	long int		start_meal;
	int				ate_meal;
	t_philo			*philo;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
};

int			ft_error(void);
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
long int	get_time(void);
void		*died(void *param);
void		lock_forks(t_philo *philo);
void		eat(t_philo *philo);
void		print_status(long int now, t_philo *philo, char *status);
void		*one_philo(t_philo *philo);

#endif