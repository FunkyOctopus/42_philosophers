/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:54:58 by olgerret          #+#    #+#             */
/*   Updated: 2021/10/04 14:39:08 by olgerret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_forks(t_input *input, t_ph *ph)
{
	int	i;

	input->forks = malloc(sizeof(pthread_mutex_t) * input->num_of_ph);
	if (input->forks == 0)
		return (-1);
	i = 0;
	while (i < input->num_of_ph)
	{
		pthread_mutex_init(&input->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&ph->wait_for_threads, NULL);
	pthread_mutex_init(&ph->wait_for_print, NULL);
	pthread_mutex_init(&ph->death_lock, NULL);
	pthread_mutex_init(&ph->run_mutex, NULL);
	return (0);
}

int	ft_negative_value_checker(t_input *input)
{
	if (input->num_of_ph < 1 || input->time_to_die < 0
		|| input->time_to_die < 0 || input->time_to_die < 0
		|| input->time_to_eat < 0 || input->time_to_sleep < 0
		|| input->min_tms_eat < 0)
	{
		write(2, "Wrong input\n", 12);
		return (-1);
	}
	return (0);
}

int	ft_argc_error(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong input\n", 12);
		return (-1);
	}
	return (0);
}

void	ft_input_parse(t_input *input, char **argv)
{
	input->num_of_ph = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		input->min_tms_eat = ft_atoi(argv[5]);
	else
		input->min_tms_eat = INT_MAX;
}

void	ft_input_init(t_input *input)
{
	input->num_of_ph = 0;
	input->time_to_die = 0;
	input->time_to_eat = 0;
	input->time_to_sleep = 0;
	input->min_tms_eat = 0;
	input->someone_died = 0;
	input->i = 0;
}
