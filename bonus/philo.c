/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:22:10 by absaid            #+#    #+#             */
/*   Updated: 2023/05/19 22:43:11 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

void	ft_filldata(t_data *data, char **av)
{
	data->nph = ft_atoi(av[0]);
	data->tdie = ft_atoi(av[1]);
	data->teat = ft_atoi(av[2]);
	data->tsleep = ft_atoi(av[3]);
	(av[4]) && (data->maxeat = ft_atoi(av[4]));
	(!av[4]) && (data->maxeat = -1);
	data->flag = true;
	// data->start = ft_current();
}

bool checkdata(t_data *data, char **av)
{
	if(data->nph < 0 || data->tdie < 0 || data->teat < 0 || 
		data->tsleep < 0 || (av[4] && data->maxeat < 0))
			return(false);
	return(true);
}

t_ph *ft_philos_create(t_data *data)
{
	int i = -1;
	t_ph *philos;

	philos = malloc(sizeof(t_ph) * data->nph);
	if(!philos)
		return(exit(1), NULL);
	while(++i < data->nph)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].neat = 0;
	}
	return(philos);
}

void	ft_procecces(t_ph *philos)
{
	t_data *data;
	int i;

	data = philos[0].data;
	i = -1;
	while(++i < philos[0].data->nph)
	{
		philos[i].pid = fork();
		(!philos[i].pid) && (ft_thread(&philos[i]), exit(0), 0);
	}
}

bool ft_sleep(unsigned int timetodo)
{
	unsigned int time = ft_current();
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
	sem_wait(philo->data->print);
	printf("%d ", ft_current() - philo->data->start);
	printf("%d %s\n", (philo->id) + 1, str);
	sem_post(philo->data->print);
}

void checkdeath(t_ph *philos)
{
	t_data *data;
	
	data = philos->data;

	while(1)
	{

		sem_wait(data->eat);
		// puts("zb");
		if(ft_current() - philos->lasteat > (unsigned int)data->tdie)
		{
			sem_wait(data->print);
			printf("%d %d died\n", ft_current() - data->start, philos->id + 1);
			data->flag = false;
			return ;
		}
		sem_post(data->eat);
		usleep(50);
		if(!checkeaiting(philos))
			return(sem_wait(data->print),(void)0);
	}
}

bool checkeaiting(t_ph *philos)
{
	t_data *data;

	data = philos->data;
	sem_wait(data->eat);
	if( philos->neat > data->maxeat && data->maxeat != -1)
		return(sem_post(data->eat), false);
	sem_post(data->eat);
	return(true);
}

unsigned int ft_current()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

bool eating(t_ph *philo)
{
	t_data *data;

	data = philo->data;
	sem_wait(data->forks);
	printlock(philo, "has taken a fork");
	sem_wait(data->forks);
	printlock(philo, "has taken a fork");
	printlock(philo, "is eating");
	if(!ft_sleep(data->teat))
		return (false);
	sem_post(data->forks);
	sem_post(data->forks);
	sem_wait(data->eat);
	// puts("zb");
	philo->lasteat = ft_current();
	philo->neat++;
	sem_post(data->eat);
	return (true);
}

void *ft_routine(void *arg)
{
	t_data *data;
	t_ph *philo = (t_ph *)arg;
	int i;
	
	i = -1;
	data = philo->data;
	(philo->id % 2) && (ft_sleep(40), 0);
	while(data->flag)
	{
		eating(philo);
		printlock(philo, "is sleeping");
		if(!ft_sleep(data->tsleep))
			return(NULL);
		printlock(philo, "is thinking");
	}
	return(NULL);
}

void	ft_thread(t_ph *philo)
{
	philo->lasteat = ft_current();
	pthread_create(&philo->n, NULL, ft_routine, philo);
	pthread_detach(philo->n);
	checkdeath(philo);
}


static void	ft_kill(t_ph *ph)
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
	return ;
}
void ft_lik_wli_3lik_wnhez_lk_rjlik_wndiro_lik_taybano_walidik(void)
{
	system("leaks philo");
}

int main(int ac, char **av)
{
	t_data *data;
	t_ph *philos;
	
	atexit(ft_lik_wli_3lik_wnhez_lk_rjlik_wndiro_lik_taybano_walidik);
	if(ac < 5 || ac > 6)
		return(puts("number of args"), 1);
	data = malloc(sizeof(t_data));
	ft_filldata(data, av + 1);
	if(!checkdata(data, av + 1))
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