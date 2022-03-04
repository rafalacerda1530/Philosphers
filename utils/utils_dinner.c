/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:39:23 by rarodrig          #+#    #+#             */
/*   Updated: 2022/03/04 01:07:41 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *died(void *param)
{
	int i;
	t_main *main;

	main = param;
	i = -1;
	while (++i < main->numb_philos)
	{
		if (get_time() - main->philo[i].last_meal > main->time_die)
		{
			print_status(get_time(), main->philo, "Morreu féla da pota");
			main->teste = 1;
			return(	NULL);
		}
		if (i+1 == main->numb_philos)
			i = -1;
		usleep(1600);
	}
	return(NULL);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_main->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->st_main->forks[philo->right_fork]);
	philo->last_meal = get_time();
	print_status(get_time(), philo, "Comendo");
	usleep(philo->st_main->time_eat * 1000);
	print_status(get_time(), philo, "Liberou o garfo");
	pthread_mutex_unlock(&philo->st_main->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->st_main->forks[philo->right_fork]);
	philo->numb_of_meals++;
}
