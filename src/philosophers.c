/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:46:12 by rarodrig          #+#    #+#             */
/*   Updated: 2022/02/21 22:18:38 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

pthread_mutex_t mutex;
int mails = 0;

void philo_info(t_main *main)
{
	int i;

	i = 0;
	while (i < main->numb_philos)
	{
		main->philo[i].n_philo = i + 1;
		main->philo[i].time = get_time();
		main->philo[i].left_fork = i;
		main->philo[i].right_fork = i + 1;  
		main->philo[i].st_main = main;
		if (i + 1 == main->numb_philos)
			main->philo[i].right_fork = 0;
		i++;
	}
}

void  start_struct(t_main *main, int argc, char **argv)
{
	main->numb_philos = ft_atoi(argv[1]);
	main->time_die = ft_atoi(argv[2]);
	main->time_eat = ft_atoi(argv[3]);
	main->time_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		main->numb_meal = ft_atoi(argv[5]);
	else
		main->numb_meal = 0;
	main->philo = malloc(sizeof(t_philo) * main->numb_philos);
	ft_bzero(main->philo, sizeof(t_philo));
	philo_info(main);
}

void *routine(void *param)
{
	t_philo *philo;
	philo = param;
	int i = 0;
	pthread_mutex_lock(&mutex);
	while (!died(philo))
	{
		i++;
	}
	pthread_mutex_lock(&mutex);
	return NULL;
}

int create_philo(t_main *main)
{
	int i;

	i = -1;
	while (++i < main->numb_philos)
	{
		main->philo[i].last_meal = get_time();
		pthread_create(&main->philo[i].thread, NULL, &routine, &main->philo[i]);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_main main;
	int i = 0;
	pthread_mutex_init(&mutex, NULL);

	(void)argv;
	if (argc < 5 || argc > 6)
		ft_error();
	// ft_bzero(&main, sizeof(t_main));
	start_struct(&main, argc, argv);
	create_philo(&main);
	while (++i < main.numb_philos)
	{
		pthread_join(main.philo[i].thread, NULL);
	}
	printf("mails = %d\n", mails);
	free(main.philo);
	return (0);
}
