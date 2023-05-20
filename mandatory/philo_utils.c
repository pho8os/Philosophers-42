/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:23:40 by absaid            #+#    #+#             */
/*   Updated: 2023/05/20 03:22:50 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

unsigned int	ft_current(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	printlock(t_ph *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%d ", ft_current() - philo->data->start);
	printf("%d %s\n", (philo->id) + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

bool	ft_sleep(t_ph *philo, unsigned int timetodo)
{
	t_data			*data;
	unsigned int	time;

	time = ft_current();
	data = philo->data;
	while (1)
	{
		if (ft_current() - time >= timetodo)
			return (true);
		usleep(50);
	}
	return (false);
}

void	checkdeath(t_ph *ph)
{
	t_data	*data;
	int		i;

	data = ph[0].data;
	while (1)
	{
		i = -1;
		while (++i < data->nph)
		{
			pthread_mutex_lock(&data->eat);
			if (ft_current() - ph[i].lasteat > (unsigned int)data->tdie)
			{
				pthread_mutex_lock(&data->print);
				printf("%d %d died\n", ft_current() - data->start, ph[i].id + 1);
				data->flag = false;
				return ;
			}
			pthread_mutex_unlock(&data->eat);
			ft_sleep(ph, 1);
		}
		if (!checkeaiting(ph))
			return (pthread_mutex_lock(&data->print), (void)0);
	}
}

bool	checkeaiting(t_ph *ph)
{
	t_data	*data;
	int		i;

	data = ph[0].data;
	i = 0;
	pthread_mutex_lock(&data->eat);
	while (i < data->nph && ph[i].neat >= data->maxeat && data->maxeat != -1)
		i++;
	pthread_mutex_unlock(&data->eat);
	if (i == data->nph)
		return (false);
	return (true);
}
