/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:46:12 by rarodrig          #+#    #+#             */
/*   Updated: 2022/03/04 20:06:32 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

pthread_mutex_t mutex;

void philo_info(t_main *main)
{
	int i;

	i = 0;
	while (i < main->numb_philos)
	{
		main->philo[i].n_philo = i + 1;
		main->philo[i].left_fork = i;
		main->philo[i].right_fork = i + 1;  
		main->philo[i].st_main = main;
		main->philo[i].last_meal = get_time();
		main->philo[i].numb_of_meals = 0;
		if (i + 1 == main->numb_philos)
			main->philo[i].right_fork = 0;
		pthread_mutex_init(&main->forks[i], NULL);
		i++;
	}
}

void  start_struct(t_main *main, int argc, char **argv)
{
	main->numb_philos = ft_atoi(argv[1]);
	if (main->numb_philos < 1)
	{
		printf("Error, numb of philos is less than 1\n");
		exit(0);
	}
	main->time_die = ft_atoi(argv[2]);
	main->time_eat = ft_atoi(argv[3]);
	main->time_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		main->numb_meal = ft_atoi(argv[5]);
	else
		main->numb_meal = 0;
	main->forks = NULL;
	main->philo = malloc(sizeof(t_philo) * main->numb_philos);
	main->forks = malloc(main->numb_philos * sizeof(pthread_mutex_t));
	main->ate_meal = 0;
	ft_bzero(main->philo, sizeof(t_philo));
	return(philo_info(main));
}

void *one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_main->forks[philo->right_fork]);
	philo->last_meal = get_time();
	print_status(get_time(), philo, "has taken a fork");
	print_status(get_time(), philo, "is eating");
	usleep(philo->st_main->time_eat * 1000);
	pthread_mutex_unlock(&philo->st_main->forks[philo->right_fork]);
	print_status(get_time(), philo, "DIED");
	philo->st_main->teste = 1;
	return(NULL);
}

void *routine(void *param)
{
	t_philo *philo;
	philo = param;

	if (philo->st_main->numb_philos == 1)
		return(one_philo(philo));
	if (philo->n_philo % 2 == 0)
			usleep(1600);
	while (philo->st_main->teste != 1)
	{
		eat(philo);
		print_status(get_time(), philo, "is sleeping");
		usleep(philo->st_main->time_sleep * 1000);
		print_status(get_time(), philo, "is thinking");
	}
	return NULL;
}

int create_philo(t_main *main)
{ 
	int i;

	i = -1;

	while (++i < main->numb_philos)
	{
		// if (main->philo[i].n_philo % 2 == 0)
		// 	usleep(1000);
		pthread_create(&main->philo[i].thread, NULL, &routine, &main->philo[i]);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_main main;
	int i = 0;
	pthread_mutex_init(&main.print, NULL);
 
	(void)argv;
	if (argc < 5 || argc > 6)
		ft_error();
	main.start_meal = get_time();
	start_struct(&main, argc, argv);
	create_philo(&main);
	pthread_create(&main.monitor, NULL, &died, &main);
	while (++i < main.numb_philos)
	{
		pthread_join(main.philo[i].thread, NULL);
	}
	pthread_join(main.monitor, NULL);
	free(main.philo);
	free(main.forks);
	return (0);
}
