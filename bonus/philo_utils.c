/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:32:08 by absaid            #+#    #+#             */
/*   Updated: 2023/05/20 03:02:25 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_kill(t_ph *ph)
{
	int		i;
	int		size;
	t_data	*data;

	data = ph[0].data;
	i = -1;
	size = data->nph;
	while (++i < size)
		kill(ph[i].pid, SIGKILL);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("eat");
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->eat);
	return ;
}

unsigned int	ft_current(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

bool	checkeaiting(t_ph *philos)
{
	t_data	*data;

	data = philos->data;
	sem_wait(data->eat);
	if (philos->neat > data->maxeat && data->maxeat != -1)
		return (sem_post(data->eat), false);
	sem_post(data->eat);
	return (true);
}

void	checkdeath(t_ph *philos)
{
	t_data	*data;

	data = philos->data;
	while (1)
	{
		sem_wait(data->death);
		if (ft_current() - philos->lasteat > (unsigned int)data->tdie)
		{
			sem_wait(data->print);
			printf("%d %d died\n", ft_current() - data->start, philos->id + 1);
			data->flag = false;
			return ;
		}
		sem_post(data->death);
		usleep(50);
		if (!checkeaiting(philos))
			return (sem_wait(data->print), (void)0);
	}
}

void	printlock(t_ph *philo, char *str)
{
	sem_wait(philo->data->print);
	printf("%d ", ft_current() - philo->data->start);
	printf("%d %s\n", (philo->id) + 1, str);
	sem_post(philo->data->print);
}
