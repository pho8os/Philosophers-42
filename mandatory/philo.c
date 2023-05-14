/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:31:27 by absaid            #+#    #+#             */
/*   Updated: 2023/05/06 17:38:06 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
void ft_mutexinit(t_data *data) // bool true or false
{
	int size;

	size = data->nph;
	data->forks = malloc(sizeof(pthread_mutex_t) * size);
	while(size-- >= 0)
		pthread_mutex_init(&data->forks[size], NULL); //learn about it and protection;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->eat, NULL);
}
void ft_filldata(t_data *data, char **av)
{
	data->nph = ft_atoi(av[0]);
	data->tdie = ft_atoi(av[1]);
	data->teat = ft_atoi(av[2]);
	data->tsleep = ft_atoi(av[3]);
	(av[4]) && (data->maxeat = ft_atoi(av[4]));
	(!av[4]) && (data->maxeat = -1);
	data->flag = true;
	ft_mutexinit(data);
}
void ft_philo_create(t_ph **philos, t_data *data) //bool return true or false
{
	int size = data->nph;
	philos = malloc(sizeof(t_ph *) * size);
	while(size-- >= 0)
	{
		philos[size] = malloc(sizeof(t_ph));
		philos[size]->id = size + 1;
		philos[size]->data = data;
		philos[size]->neat = 0;
	}
}
bool ft_checkdata(t_data *data, char **av)
{
	if(data->nph < 0 || data->tdie < 0 || data->teat < 0 || 
		data->tsleep < 0 || (av[4] && data->maxeat < 0))
			return(false);
	return(true);
}
void ft_routine()
{
	
}
unsigned int ft_current()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_thread(t_ph **philos)
{
	t_data *data;
	int th;
	int i = -1;
	data = philos[0]->data;
	while(++i < data->nph)
	{
		philos[i]->lasteat = ft_current();
		pthread_create(&th, NULL, &ft_routine, philos[i]);//check true or false; 
	}
}

int main(int ac, char **av)
{
	if(ac < 5 || ac > 6)
		return(puts("number of args"), 1);
	t_data data;
	t_ph **philos;
	filldata(&data, av + 1);
	if(!checkdata(&data, av + 1))
		return (puts("unvalid args"), 1);
	ft_philo_create(philos, &data);
	
	
}