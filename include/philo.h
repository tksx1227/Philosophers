/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 15:06:51 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>

typedef long long				t_timestamp;
typedef struct s_philo			t_philo;
typedef struct s_global_info	t_global_info;

struct s_philo
{
	int				index;
	bool			exist_my_fork;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	t_philo			*prev;
	t_philo			*next;
	int				eat_count;
	t_timestamp		last_ate_at_us;
	t_global_info	*info;
};

struct s_global_info
{
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_times_each_philo_must_eat;
	bool			is_finished;
	pthread_mutex_t	system_status_mutex;
};

/* Utils */
int			parse_args(int params[], int argc, char **argv);
void		ft_putstr_fd(char const *s, int fd);
void		print_usage(void);
void		init_global_info(t_global_info *info, int params[]);
void		msleep(unsigned int ms);
t_timestamp	get_timestamp_us(void);

/* Philo Utils */
t_philo		*get_philos_circular(t_global_info *info);
void		free_philos_circular(t_philo *head);

/* Philo Actions */
int			take_two_forks(t_philo *philo);
int			return_two_forks(t_philo *philo);
int			do_eating(t_philo *philo);
int			do_sleeping(t_philo *philo);
int			do_thinking(t_philo *philo);

/* Philo thread */
int			start_all_threads(t_philo *head);
int			join_all_threads(t_philo *head);

#endif
