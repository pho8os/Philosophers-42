/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:31:36 by absaid            #+#    #+#             */
/*   Updated: 2023/05/15 18:37:47 by absaid           ###   ########.fr       */
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

typedef struct s_data
{
	int	nph;
	int	tdie;
	int	teat;
	unsigned int start;
	int	tsleep;
	int	maxeat;
	bool flag;
	pthread_mutex_t print;
	pthread_mutex_t eat;
	pthread_mutex_t *forks;
} t_data;

typedef struct s_ph
{
	pthread_t n;
	int		id;
	t_data	*data;
	int		neat;
	unsigned int	lasteat;
} t_ph;
int ft_atoi(char *str);
void	*ft_routine(void *arg);
void ft_mutexinit(t_data *data) ;
void ft_filldata(t_data *data, char **av);
t_ph **ft_philo_create(t_data *data);
bool checkdata(t_data *data, char **av);
void ft_thread(t_ph **philos);
unsigned int ft_current();
bool ft_sleep(t_ph *philo, unsigned int timetodo);
void printlock(t_ph *philo, char *str);
bool eating(t_ph *philo);
#endif