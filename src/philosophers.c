/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:46:12 by rarodrig          #+#    #+#             */
/*   Updated: 2022/03/05 01:18:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_info(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->numb_philos)
	{
		main->philo[i].n_philo = i + 1;
		main->philo[i].left_fork = i;
		main->philo[i].right_fork = i + 1;
		main->philo[i].st_main = main;
		main->philo[i].last_meal = get_time();
		main->philo[i].n_meals = 0;
		if (i + 1 == main->numb_philos)
			main->philo[i].right_fork = 0;
		pthread_mutex_init(&main->forks[i], NULL);
		i++;
	}
}

void	start_struct(t_main *main, int argc, char **argv)
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
	return (philo_info(main));
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->st_main->numb_philos == 1)
		return (one_philo(philo));
	if (philo->n_philo % 2 == 0)
		usleep(1600);
	while (philo->st_main->checker != 1)
	{
		eat(philo);
		print_status(get_time(), philo, "is sleeping");
		usleep(philo->st_main->time_sleep * 1000);
		print_status(get_time(), philo, "is thinking");
		philo->n_meals++;
	}
	return (NULL);
}

int	create_philo(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->numb_philos)
		pthread_create(&main->philo[i].thread, NULL, &routine, &main->philo[i]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_main	main;
	int		i;

	i = 0;
	pthread_mutex_init(&main.print, NULL);
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
