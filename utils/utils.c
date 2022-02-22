/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 23:35:07 by rarodrig          #+#    #+#             */
/*   Updated: 2022/02/18 21:49:44 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	cont;

	res = 0;
	sign = 1;
	cont = 0;
	while (nptr[cont] == ' ' || (nptr[cont] >= '\t' && nptr[cont] <= '\r' ))
	{
		cont++;
	}
	if (nptr[cont] == '+' || nptr[cont] == '-')
	{
		if (nptr[cont] == '-')
		{
			sign *= -1;
		}
		cont++;
	}
	while (nptr[cont] >= '0' && nptr[cont] <= '9')
	{
		res = nptr[cont] - '0' + (res * 10);
		cont++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	printf("c = %d\n", c);
	if (c >= '0' && c <= 2147483647)
	{
		return (0);
	}
	return (1);
}

int ft_error(void)
{
	printf("Error\n");
	exit (1);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_s;
	size_t			i;

	i = 0;
	s_s = (unsigned char *)s;
	while (i < n)
	{
		s_s[i] = '\0';
		i++;
	}
}

long int    get_time(void)
{
    struct timeval    tv;
    long int        milliseconds;

    gettimeofday(&tv, NULL);
    milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (milliseconds);
}