/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:39:23 by rarodrig          #+#    #+#             */
/*   Updated: 2022/03/05 01:18:01 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*died(void *param)
{
	int		i;
	t_main	*main;

	main = param;
	i = -1;
	while (++i < main->numb_philos)
	{
		if (get_time() - main->philo[i].last_meal > main->time_die)
		{
			print_status(get_time(), main->philo, "DIED");
			main->checker = 1;
			return (NULL);
		}
		if (main->philo[i].n_meals == main->numb_meal && main->numb_meal > 0)
			main->ate_meal++;
		if (main->ate_meal == main->numb_philos)
		{
			main->checker = 1;
			return (NULL);
		}
		if (i + 1 == main->numb_philos)
			i = -1;
		usleep(1600);
	}
	return (NULL);
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_main->forks[philo->right_fork]);
	philo->last_meal = get_time();
	print_status(get_time(), philo, "has taken a fork");
	print_status(get_time(), philo, "is eating");
	usleep(philo->st_main->time_eat * 1000);
	pthread_mutex_unlock(&philo->st_main->forks[philo->right_fork]);
	print_status(get_time(), philo, "DIED");
	philo->st_main->checker = 1;
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_main->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->st_main->forks[philo->right_fork]);
	philo->last_meal = get_time();
	print_status(get_time(), philo, "has taken a fork");
	print_status(get_time(), philo, "has taken a fork");
	print_status(get_time(), philo, "is eating");
	usleep(philo->st_main->time_eat * 1000);
	pthread_mutex_unlock(&philo->st_main->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->st_main->forks[philo->right_fork]);
}
