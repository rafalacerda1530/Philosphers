/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:11:28 by rarodrig          #+#    #+#             */
/*   Updated: 2022/03/03 20:25:32 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(long int now, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->st_main->print);
	if(philo->st_main->teste != 1)
		printf("%6ld %3d %s\n", now - philo->st_main->start_meal, philo->n_philo, status);
	// printf("teste");
	pthread_mutex_unlock(&philo->st_main->print);
}
