/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:42:21 by absaid            #+#    #+#             */
/*   Updated: 2023/05/20 02:59:16 by absaid           ###   ########.fr       */
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

void	ft_filldata(t_data *data, char **av)
{
	data->nph = ft_atoi(av[0]);
	data->tdie = ft_atoi(av[1]);
	data->teat = ft_atoi(av[2]);
	data->tsleep = ft_atoi(av[3]);
	(av[4]) && (data->maxeat = ft_atoi(av[4]));
	(!av[4]) && (data->maxeat = -1);
	data->flag = true;
}

bool	checkdata(t_data *data, char **av)
{
	if (data->nph < 0 || data->tdie < 0 || data->teat < 0
		|| data->tsleep < 0 || (av[4] && data->maxeat < 0))
		return (false);
	return (true);
}

t_ph	*ft_philos_create(t_data *data)
{
	int		i;
	t_ph	*philos;

	i = -1;
	philos = malloc(sizeof(t_ph) * data->nph);
	if (!philos)
		return (exit(1), NULL);
	while (++i < data->nph)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].neat = 0;
	}
	return (philos);
}

void	ft_procecces(t_ph *philos)
{
	t_data	*data;
	int		i;

	data = philos[0].data;
	i = -1;
	while (++i < philos[0].data->nph)
	{
		philos[i].pid = fork();
		(!philos[i].pid) && (ft_thread(&philos[i]), exit(0), 0);
	}
}
