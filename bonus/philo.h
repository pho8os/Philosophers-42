/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:22:13 by absaid            #+#    #+#             */
/*   Updated: 2023/05/19 09:20:15 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include<sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_data
{
	int	nph;
	int	tdie;
	int	teat;
	unsigned int start;
	int	tsleep;
	int	maxeat;
	bool flag;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*eat;
} t_data;

typedef struct s_ph
{
	int pid;
	pthread_t n;
	int		id;
	t_data	*data;
	int		neat;
	unsigned int	lasteat;
} t_ph;

void	ft_thread(t_ph *philo);
void *ft_routine(void *arg);
bool eating(t_ph *philo);
unsigned int ft_current();
bool checkeaiting(t_ph *philos);
void checkdeath(t_ph *philos);
void printlock(t_ph *philo, char *str);
bool ft_sleep(unsigned int timetodo);
t_ph *ft_philos_create(t_data *data);
void	ft_procecces(t_ph *philos);
bool checkdata(t_data *data, char **av);
int ft_atoi(char *str);

#endif