/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:42:21 by absaid            #+#    #+#             */
/*   Updated: 2023/05/05 16:53:07 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include<limits.h>

int ft_atoi(char *str)
{
	long int	res;
	int			i;
	
	res = 0;
	i = 0;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	if(str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			return(-1);
		i++;
	}
	while(str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res += (res * 10) + (str[i] - 48);
		i++;
		if(res > INT_MAX)
			return(-1);
	}
	if(str[i])
		return(-1);
	return(res);
}