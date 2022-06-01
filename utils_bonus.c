/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:11:00 by nbenjami          #+#    #+#             */
/*   Updated: 2022/06/02 00:21:56 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static int	ft_isSpaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	getMaxMin(int currentValue, int currNum, int sign)
{
	if ((currentValue > 214748364)
		|| (currentValue == 214748364 && currNum > 8))
	{
		if (sign > 0)
			return (-1);
		if (sign < 0)
			return (0);
	}
	if (currentValue <= 214748364 && currNum <= 7)
		return ((currentValue * 10 + currNum) * sign);
	if (currentValue == 214748364 && currNum == 8)
	{
		if (sign > 0)
			return ((currentValue * 10 + 7) * sign);
		if (sign < 0)
			return ((currentValue * 10 + currNum) * sign);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	value;
	int	sign;

	sign = 1;
	value = 0;
	while (ft_isSpaces(*str) && *str != '\0')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = sign * (-1);
	if (!*str)
		return (-1);
	if (*str >= '0' && *str <= '9')
	{
		while (*str && (*str >= '0' && *str <= '9'))
		{
			if (value <= 214748364)
				value = value * 10 + (*str - '0');
			else
				return (value = getMaxMin(value, *str - '0', sign));
			str++;
		}
	}
	return (value * sign);
}

void	ft_usleep(time_t milisec, long start_time)
{
	time_t	stop;
	time_t	start;

	stop = get_current_time(start_time) + milisec;
	start = get_current_time(start_time);
	while (start < stop)
	{
		usleep(10);
		start = get_current_time(start_time);
	}
}
