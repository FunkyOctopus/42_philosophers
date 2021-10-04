/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:55:13 by olgerret          #+#    #+#             */
/*   Updated: 2021/10/04 14:08:16 by olgerret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*ft_mayor(void *arg)
{
	t_ph	*ph;
	int		i;

	ph = (t_ph *)arg;
	i = 0;
	while (1)
	{
		if (ft_get_time() >= ph[i].death_time)
		{
			ft_printer(&ph[i], 'D');
			ft_stop_program(ph);
			if (ph[i].input_data->someone_died == 1)
				return (NULL);
		}
		i++;
		if (i >= ph[0].input_data->num_of_ph)
			i = 0;
	}
	return (NULL);
}

void	ft_eating(t_ph *ph)
{
	if (ph->input_data->someone_died == 0)
	{	
		pthread_mutex_lock(ph->left_fork);
		ft_printer(ph, 'F');
		pthread_mutex_lock(ph->right_fork);
		ft_printer(ph, 'F');
		ft_printer(ph, 'E');
		ft_sleep(ph->input_data->time_to_eat);
		ph->death_time = ft_get_time() + ph->input_data->time_to_die;
		ph->min_tms_eat_ph -= 1;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		if (ph->min_tms_eat_ph == 0)
		{
			ph->run_program = 0;
			ft_unlock_everything(ph);
		}
	}
}

void	*ft_process_sender(void *arg)
{	
	t_ph	*ph;

	ph = (t_ph *)arg;
	pthread_mutex_lock(&ph->wait_for_threads);
	while (ph->run_program == 1)
	{
		if (ph->input_data->someone_died == 0)
		{
			ph->death_time = ft_get_time() + ph->input_data->time_to_die;
			ft_eating(ph);
			if (ph->run_program == 1)
			{
				ft_printer(ph, 'S');
				ft_sleep(ph->input_data->time_to_sleep);
				ft_printer(ph, 'T');
			}
		}
	}
	pthread_mutex_unlock(&ph->wait_for_threads);
	ft_unlock_everything(ph);
	return (NULL);
}

void	ft_thread_sender(t_input *input, t_ph *ph)
{
	pthread_t	mayor;

	input->i = 0;
	input->start_time = ft_get_time();
	while (input->i < input->num_of_ph)
	{
		if (input->i % 2 == 0)
			pthread_create(&ph[input->i].th,
				NULL, &ft_process_sender, &ph[input->i]);
		usleep(100);
		input->i++;
	}
	usleep(100);
	input->i = 0;
	while (input->i < input->num_of_ph)
	{
		if (input->i % 2 != 0)
			pthread_create(&ph[input->i].th,
				NULL, &ft_process_sender, &ph[input->i]);
		usleep(100);
		input->i++;
	}
	pthread_create(&mayor, NULL, &ft_mayor, ph);
}

int	ft_philosophers(t_input *input, t_ph *ph)
{
	while (input->i < input->num_of_ph)
	{
		ph[input->i].input_data = input;
		ph[input->i].philo_number = input->i + 1;
		ph[input->i].min_tms_eat_ph = input->min_tms_eat;
		if (input->i < input->num_of_ph)
		{
			ph[input->i].left_fork = &input->forks[input->i];
			ph[input->i].run_program = 1;
			if (input->i == 0)
				ph[input->i].right_fork = &input->forks[input->num_of_ph - 1];
			else
				ph[input->i].right_fork = &input->forks[input->i - 1];
		}
		input->i++;
	}
	ft_thread_sender(input, ph);
	return (0);
}
