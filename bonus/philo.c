/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:22:10 by absaid            #+#    #+#             */
/*   Updated: 2023/05/20 03:00:34 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_sleep(unsigned int timetodo)
{
	unsigned int	time;

	time = ft_current();
	while (1)
	{
		if (ft_current() - time >= timetodo)
			return (true);
		usleep(50);
	}
	return (false);
}

bool	eating(t_ph *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks);
	printlock(philo, "has taken a fork");
	sem_wait(data->forks);
	printlock(philo, "has taken a fork");
	printlock(philo, "is eating");
	if (!ft_sleep(data->teat))
		return (false);
	sem_post(data->forks);
	sem_post(data->forks);
	sem_wait(data->eat);
	philo->lasteat = ft_current();
	philo->neat++;
	sem_post(data->eat);
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
	(philo->id % 2) && (ft_sleep(40), 0);
	while (data->flag)
	{
		eating(philo);
		printlock(philo, "is sleeping");
		if (!ft_sleep(data->tsleep))
			return (NULL);
		printlock(philo, "is thinking");
	}
	return (NULL);
}

void	ft_thread(t_ph *philo)
{
	philo->lasteat = ft_current();
	pthread_create(&philo->n, NULL, ft_routine, philo);
	pthread_detach(philo->n);
	checkdeath(philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_ph	*philos;

	if (ac < 5 || ac > 6)
		return (puts("number of args"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_filldata(data, av + 1);
	if (!checkdata(data, av + 1))
		return (free(data), printf("unvalid args"), 1);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("eat");
	data->forks = sem_open("fork", O_CREAT, 0600, data->nph);
	data->print = sem_open("print", O_CREAT, 0600, 1);
	data->eat = sem_open("eat", O_CREAT, 0600, 1);
	philos = ft_philos_create(data);
	data->start = ft_current();
	(philos) && (ft_procecces(philos), 0);
	waitpid(-1, NULL, 0);
	ft_kill(philos);
}
