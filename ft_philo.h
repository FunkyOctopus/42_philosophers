/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 07:38:52 by olgerret          #+#    #+#             */
/*   Updated: 2021/10/04 14:40:08 by olgerret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>	
# include <pthread.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_input
{
	int				num_of_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_tms_eat;

	int				someone_died;
	int				i;
	long			start_time;
	pthread_mutex_t	*forks;
}				t_input;

typedef struct s_ph
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	wait_for_threads;
	pthread_mutex_t	wait_for_print;	
	pthread_mutex_t	death_lock;
	pthread_mutex_t	run_mutex;
	pthread_t		th;
	t_input			*input_data;

	int				philo_number;
	int				min_tms_eat_ph;
	int				run_program;
	long			death_time;
}				t_ph;

int		main(int argc, char **argv);

int		ft_atoi(const char *str);
void	ft_sleep(long time);
long	ft_get_time(void);
int		ft_printer(t_ph *ph, char message);
void	ft_funeral(t_ph *ph, long time);

void	ft_input_init(t_input *input);
void	ft_input_parse(t_input *input, char **argv);
int		ft_argc_error(int argc);
int		ft_negative_value_checker(t_input *input);
int		ft_forks(t_input *input, t_ph *ph);

int		ft_philosophers(t_input *input, t_ph *ph);
void	ft_thread_sender(t_input *input, t_ph *ph);
void	*ft_process_sender(void *arg);
void	ft_eating(t_ph *ph);
void	*ft_mayor(void *arg);

void	ft_lock_everything(t_ph *ph);
void	ft_unlock_everything(t_ph *ph);
void	ft_stop_program(t_ph *ph);
void	ft_join(t_input *input, t_ph *ph);
void	ft_free(t_input *input, t_ph *ph);

#endif
