/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:54:58 by olgerret          #+#    #+#             */
/*   Updated: 2021/10/04 14:39:11 by olgerret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_funeral(t_ph *ph, long time)
{	
	pthread_mutex_lock(&ph->death_lock);
	ph->input_data->someone_died = 1;
	pthread_mutex_unlock(&ph->death_lock);
	printf("%ld		%d	died\n", time, ph->philo_number);
}

int	ft_printer(t_ph *ph, char message)
{
	long	time;

	pthread_mutex_lock(&ph->wait_for_print);
	if (ph->input_data->someone_died == 0)
	{
		time = ft_get_time() - ph->input_data->start_time;
		if (message == 'F')
			printf("%ld		%d	has taken a fork\n", time, ph->philo_number);
		if (message == 'E')
			printf("%ld		%d	is eating\n", time, ph->philo_number);
		if (message == 'S')
			printf("%ld		%d	is sleeping\n", time, ph->philo_number);
		if (message == 'T')
			printf("%ld		%d	is thinking\n", time, ph->philo_number);
		if (message == 'D')
		{
			ft_funeral(ph, time);
			return (-1);
		}
	}
	pthread_mutex_unlock(&ph->wait_for_print);
	return (0);
}

long	ft_get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = (tp.tv_sec * 1000);
	milliseconds += (tp.tv_usec / 1000);
	return (milliseconds);
}

void	ft_sleep(long time)
{
	long	start_time;

	start_time = ft_get_time();
	while (start_time + time > ft_get_time())
		usleep(100);
	return ;
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX || (str[i] < '0' && str[i] != '\0')
		|| (str[i] > '9' && str[i] != '\0'))
		return (-1);
	return ((int)(result));
}
