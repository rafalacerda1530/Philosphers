/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:39:23 by rarodrig          #+#    #+#             */
/*   Updated: 2022/02/21 22:18:56 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int died(t_philo *philo)
{
	int i;

	i = 0;

	while (i < philo->st_main->numb_philos)
	{
		printf("id = %d / time = %ld\n",philo->st_main->philo[i].n_philo, get_time() - philo->st_main->philo[i].last_meal);
		if (get_time() - philo->st_main->philo[i].last_meal > philo->st_main->time_die)
		{
			printf("Morreu = %d", philo->st_main->philo[i].n_philo);
			// free(philo);
			exit (1);
		}
		i++;
	}
	return(0);
}