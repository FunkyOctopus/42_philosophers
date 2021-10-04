/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:55:13 by olgerret          #+#    #+#             */
/*   Updated: 2021/10/04 14:38:59 by olgerret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	main(int argc, char **argv)
{
	t_input	*input;
	t_ph	*ph;

	input = malloc(sizeof(t_input));
	if (input == 0)
		return (-1);
	if (ft_argc_error(argc) != 0)
		return (-1);
	ft_input_init(input);
	ft_input_parse(input, argv);
	if (ft_negative_value_checker(input) != 0)
	{
		free(input);
		return (-1);
	}
	ph = malloc(sizeof(t_ph) * input->num_of_ph + 1);
	if (ph == 0)
		return (-1);
	ft_forks(input, ph);
	ft_philosophers(input, ph);
	ft_join(input, ph);
	ft_free(input, ph);
	return (0);
}
