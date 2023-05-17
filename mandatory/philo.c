/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:31:27 by absaid            #+#    #+#             */
/*   Updated: 2023/05/17 11:35:02 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
void ft_mutexinit(t_data *data) // bool true or false
{
	int size;
	int i = -1;
	size = data->nph;
	data->forks = malloc(sizeof(pthread_mutex_t) * size);
	while(++i <= size)
		pthread_mutex_init(&data->forks[i], NULL); //learn about it and protection;	
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->forflag, NULL);
}
void ft_filldata(t_data *data, char **av)
{
	data->nph = ft_atoi(av[0]);
	data->tdie = ft_atoi(av[1]);
	data->teat = ft_atoi(av[2]);
	printf("%d nph \n",data->nph);
	data->tsleep = ft_atoi(av[3]);
	(av[4]) && (data->maxeat = ft_atoi(av[4]));
	(!av[4]) && (data->maxeat = -1);
	data->flag = true;
	data->start = ft_current();
	ft_mutexinit(data);
}
t_ph **ft_philo_create(t_data *data) //bool return true or false
{
	t_ph **philos;
	
	int size = data->nph;
	philos = malloc(sizeof(t_ph *) * size);
	int  i = -1; 
	while(++i < size)
	{
		philos[i] = malloc(sizeof(t_ph));
		philos[i]->id = i ;
		philos[i]->data = data;
		philos[i]->neat = 0;
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

bool checkeaiting(t_ph **philos)
{
	t_data *data;
	int i;

	data = philos[0]->data;
	i = 0;
	pthread_mutex_lock(&data->eat);
	while(i < data->nph && philos[i]->neat >= data->maxeat && data->maxeat != -1)
		i++;
	pthread_mutex_unlock(&data->eat);
	if(i == data->nph)
		return(false);
	return(true);
}

void checkdeath(t_ph **philos)
{
	t_data *data;
	int i;
	
	data = philos[0]->data;

	while(1)
	{
		i = -1;
		while(++i < data->nph)
		{
			pthread_mutex_lock(&data->eat);
			if(ft_current() - philos[i]->lasteat > (unsigned int)data->tdie)
			{
				printlock(philos[i], "died");
				// data->flag = false;
				pthread_mutex_lock(&data->print);
				return ;
			}
			pthread_mutex_unlock(&data->eat);
			usleep(50);
		}
		if(!checkeaiting(philos))
			{
				pthread_mutex_lock(&data->print);
				return ;
			}
	}
}

void ft_thread(t_ph **philos)
{
	t_data *data;
	
	int i = -1;
	data = philos[0]->data;
	while(++i < data->nph)
	{
		philos[i]->lasteat = ft_current();
		if(pthread_create(&philos[i]->n, NULL, ft_routine, philos[i]))
			return ;//check true or false; 
	}
	i = -1;
	while(++i < data->nph)
		pthread_detach(philos[i]->n);//check true or false;
	checkdeath(philos);
	// i = -1;
	// while(++i < data->nph)
	// 	pthread_mutex_destroy(&data->forks[i]);
	// free_m3ks(philos);
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
	printf("%d %s\n", philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

bool eating(t_ph *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	printlock(philo, "has taken a fork");
	if(data->nph == 1)
		return(ft_sleep(philo, data->tdie), false);
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nph]);
	printlock(philo, "has taken a fork");
	printlock(philo, "is eating");
	if(!ft_sleep(philo, data->teat))
		return (false);
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->nph]);
	pthread_mutex_unlock(&data->forks[philo->id]);
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
	if(philo->id % 2)
		while(++i <= 500)
			usleep(1);
	
	while(1)
	{
		if(!eating(philo))
			return(NULL) ;
		printlock(philo, "is sleeping");
		if(!ft_sleep(philo, data->tsleep))
			return(NULL);
		printlock(philo, "is thinking");
		// pthread_mutex_lock(&data->print);
	}
	return(NULL);
}

int main(int ac, char **av)
{
	if(ac < 5 || ac > 6)
		return(puts("number of args"), 1);
	t_data data;
	ft_filldata(&data, av + 1);
	if(!checkdata(&data, av + 1))
		return (puts("unvalid args"), 1);

	t_ph **philos = ft_philo_create(&data);
	ft_thread(philos);
}