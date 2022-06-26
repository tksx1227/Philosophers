/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/26 22:34:09 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>

typedef unsigned long long	t_timestamp;

typedef enum e_status
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
}	t_status;

typedef struct s_gen_info
{
	int	n_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_of_times_each_philo_must_eat;
}	t_gen_info;

/* Utils */
void				ft_putstr_fd(char const *s, int fd);
void				print_usage(void);
void				parse_args(int params[], int argc, char **argv);
void				init_philo_info(t_philo_info *philo_info, int params[]);
t_timestamp	get_timestamp_ms(void);

#endif
