/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:31:27 by absaid            #+#    #+#             */
/*   Updated: 2023/05/20 03:20:51 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_ph	*ft_philo_create(t_data *data)
{
	t_ph	*philos;
	int		size;
	int		i;

	size = data->nph;
	philos = malloc(sizeof(t_ph) * size);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		philos[i].id = i ;
		philos[i].data = data;
		philos[i].neat = 0;
	}
	return (philos);
}

void	ft_thread(t_ph *philos)
{
	t_data	*data;
	int		i;

	i = -1;
	data = philos[0].data;
	while (++i < data->nph)
	{
		philos[i].lasteat = ft_current();
		pthread_create(&philos[i].n, NULL, ft_routine, &philos[i]);
		pthread_detach(philos[i].n);
	}
	checkdeath(philos);
}

bool	eating(t_ph *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	printlock(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nph]);
	printlock(philo, "has taken a fork");
	printlock(philo, "is eating");
	if (!ft_sleep(philo, data->teat))
		return (false);
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->nph]);
	pthread_mutex_lock(&data->eat);
	philo->lasteat = ft_current();
	philo->neat++;
	pthread_mutex_unlock(&data->eat);
	return (true);
}

void	*ft_routine(void *arg)
{
	t_data	*data;
	t_ph	*philo;
	int		i;

	philo = (t_ph *)arg;
	i = -1;
	data = philo->data;
	(philo->id % 2) && (ft_sleep(philo, 50), 0);
	while (data->flag)
	{
		if (!eating(philo))
			return (NULL);
		printlock(philo, "is sleeping");
		if (!ft_sleep(philo, data->tsleep))
			return (NULL);
		printlock(philo, "is thinking");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_ph	*philos;

	if (ac < 5 || ac > 6)
		return (printf("number of args"), 1);
	data = malloc(sizeof(t_data));
	ft_filldata(data, av + 1);
	if (!checkdata(data, av + 1))
		return (free(data), printf("unvalid args"), 1);
	ft_mutexinit(data);
	philos = ft_philo_create(data);
	(philos) && (ft_thread(philos), 0);
}
