/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:31:27 by absaid            #+#    #+#             */
/*   Updated: 2023/05/19 02:23:57 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
void ft_mutexinit(t_data *data) 
{
	int size;
	int i = -1;
	size = data->nph;
	data->forks = malloc(sizeof(pthread_mutex_t) * size);
	while(++i < size)
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
t_ph *ft_philo_create(t_data *data)
{
	t_ph *philos;
	
	int size = data->nph;
	philos = malloc(sizeof(t_ph ) * size);
	int  i = -1; 
	while(++i < size)
	{
		philos[i].id = i ;
		philos[i].data = data;
		philos[i].neat = 0;
	}
	return(philos);
}
bool checkdata(t_data *data, char **av)
{
	if(data->nph < 0 || data->tdie < 0 || data->teat < 0 || 
		data->tsleep < 0 || (av[4] && data->maxeat < 0))
			return(false);
	return(true);
}

unsigned int ft_current()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

bool checkeaiting(t_ph *philos)
{
	t_data *data;
	int i;

	data = philos[0].data;
	i = 0;
	pthread_mutex_lock(&data->eat);
	while(i < data->nph && philos[i].neat >= data->maxeat && data->maxeat != -1)
		i++;
	pthread_mutex_unlock(&data->eat);
	if(i == data->nph)
		return(false);
	return(true);
}

void checkdeath(t_ph *philos)
{
	t_data *data;
	int i;
	
	data = philos[0].data;

	while(1)
	{
		i = -1;
		while(++i < data->nph)
		{
			pthread_mutex_lock(&data->eat);
			if(ft_current() - philos[i].lasteat > (unsigned int)data->tdie)
			{
				pthread_mutex_lock(&data->print);
				printf("%d %d died\n", ft_current() - data->start, philos[i].id + 1);
				data->flag = false;
				return ;
			}
			pthread_mutex_unlock(&data->eat);
			ft_sleep(philos,1);
		}
		if(!checkeaiting(philos))
			return(pthread_mutex_lock(&data->print), (void)0);
	}
}

void ft_thread(t_ph *philos)
{
	t_data *data;
	
	int i = -1;
	data = philos[0].data;
	while(++i < data->nph)
	{
		philos[i].lasteat = ft_current();
		pthread_create(&philos[i].n, NULL, ft_routine, &philos[i]);
		pthread_detach(philos[i].n);
	}

	checkdeath(philos);
}

bool ft_sleep(t_ph *philo, unsigned int timetodo)
{
	t_data *data;

	unsigned int time = ft_current();
	data = philo->data;
	
	while(1)
	{
		if(ft_current() - time >= timetodo)
			return(true);
		usleep(50);
	}

	return(false);
}

void printlock(t_ph *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%d ", ft_current() - philo->data->start);
	printf("%d %s\n", (philo->id) + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

bool eating(t_ph *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	printlock(philo, "has taken a fork");
	// if(data->nph == 1)
	// 	return(ft_sleep(philo, data->tdie), false);
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nph]);
	printlock(philo, "has taken a fork");
	printlock(philo, "is eating");
	if(!ft_sleep(philo, data->teat))
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
	t_data *data;
	t_ph *philo = (t_ph *)arg;
	int i;
	
	i = -1;
	data = philo->data;
	(philo->id % 2) && (ft_sleep(philo, 50), 0);
	while(data->flag)
	{
		if(!eating(philo))
			return(NULL) ;
		printlock(philo, "is sleeping");
		if(!ft_sleep(philo, data->tsleep))
			return(NULL);
		printlock(philo, "is thinking");
	}
	return(NULL);
}
void ft_lik_wli_3lik_wndiro_bin_rjlik(void)
{
	system("leaks philo");
}

int main(int ac, char **av)
{
	atexit(ft_lik_wli_3lik_wndiro_bin_rjlik);
	if(ac < 5 || ac > 6)
		return(puts("number of args"), 1);
	t_data *data;
	data = malloc(sizeof(t_data));
	ft_filldata(data, av + 1);
	if(!checkdata(data, av + 1))
		return (free(data), puts("unvalid args"), 1);
	ft_mutexinit(data);

	t_ph *philos = ft_philo_create(data);
	ft_thread(philos);
	if(data->nph == 1)
	{
		free(philos);
		free(data->forks);
		free(data);
	}
}