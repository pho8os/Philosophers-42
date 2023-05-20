/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:42:21 by absaid            #+#    #+#             */
/*   Updated: 2023/05/20 03:18:36 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include<limits.h>

int	ft_atoi(char *str)
{
	long int	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
		if (res > INT_MAX)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (res);
}

bool	checkdata(t_data *data, char **av)
{
	if (data->nph < 0 || data->tdie < 0 || data->teat < 0
		|| data->tsleep < 0 || (av[4] && data->maxeat < 0))
		return (false);
	return (true);
}

void	ft_mutexinit(t_data *data)
{
	int	size;
	int	i;

	size = data->nph;
	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * size);
	while (++i < size)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->eat, NULL);
}

void	ft_filldata(t_data *data, char **av)
{
	data->nph = ft_atoi(av[0]);
	data->tdie = ft_atoi(av[1]);
	data->teat = ft_atoi(av[2]);
	data->tsleep = ft_atoi(av[3]);
	(av[4]) && (data->maxeat = ft_atoi(av[4]));
	(!av[4]) && (data->maxeat = -1);
	data->flag = true;
	data->start = ft_current();
}
