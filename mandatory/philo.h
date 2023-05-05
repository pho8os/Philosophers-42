/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:31:36 by absaid            #+#    #+#             */
/*   Updated: 2023/05/05 16:12:48 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

typedef struct s_data
{
	int	nph;
	int	tdie;
	int	teat;
	int	tsleep;
	int	maxeat;
	bool flag;
	pthread_mutex_t *forks;
} t_data;

typedef struct s_ph
{
	int		id;
	t_data	*data;
	int		neat;
	unsigned int	lasteat;
} t_ph;
int ft_atoi(char *str);


#endif