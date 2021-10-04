/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:16:40 by olgerret          #+#    #+#             */
/*   Updated: 2021/10/04 13:17:48 by olgerret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_free(t_input *input, t_ph *ph)
{
	free(input->forks);
	free(input);
	free(ph);
}

void	ft_join(t_input *input, t_ph *ph)
{
	int	i;

	i = 0;
	while (i < input->num_of_ph)
	{
		pthread_join(ph[i].th, NULL);
		i++;
	}
	i = 0;
	while (i < input->num_of_ph)
	{
		pthread_mutex_destroy(&ph->input_data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&ph->wait_for_threads);
	pthread_mutex_destroy(&ph->wait_for_print);
	pthread_mutex_destroy(&ph->death_lock);
	pthread_mutex_destroy(&ph->run_mutex);
}

void	ft_stop_program(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->input_data->num_of_ph)
	{
		ph[i].input_data->someone_died = 1;
		ph[i].run_program = 0;
		ft_unlock_everything(&ph[i]);
		i++;
	}
}

void	ft_unlock_everything(t_ph *ph)
{
	pthread_mutex_unlock(&ph->wait_for_threads);
	pthread_mutex_unlock(&ph->wait_for_print);
	pthread_mutex_unlock(&ph->run_mutex);
	pthread_mutex_unlock(ph->input_data->forks);
	pthread_mutex_unlock(&ph->death_lock);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	ft_lock_everything(t_ph *ph)
{
	pthread_mutex_lock(ph->input_data->forks);
	pthread_mutex_lock(&ph->wait_for_threads);
	pthread_mutex_lock(&ph->wait_for_print);
}
