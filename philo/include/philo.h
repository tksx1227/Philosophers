/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/04 17:58:56 by ttomori          ###   ########.fr       */
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

# define CREATE_PHILO_INTERVAL 100
# define OBSERVE_INTERVAL 1000

typedef long long				t_timestamp;
typedef enum e_action			t_action;
typedef struct s_philo			t_philo;
typedef struct s_global_info	t_global_info;

enum e_action
{
	TAKE_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
};

struct s_philo
{
	int				index;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	t_philo			*prev;
	t_philo			*next;
	size_t			eat_count;
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
	bool			is_system_stopped;
	pthread_mutex_t	system_status_mutex;
};

/* Utils */
int			parse_args(int params[], int argc, char **argv);
int			init_global_info(t_global_info *info, int params[]);
int			msleep_precise(unsigned int ms);
void		print_usage(void);
t_timestamp	get_current_time_us(void);

/* Philo Utils */
int			init_philos_circular(t_philo **head_p, t_global_info *info);
int			free_philos_circular(t_philo *head);

/* Philo Actions */
int			take_two_forks(t_philo *philo);
int			release_two_forks(t_philo *philo);
int			do_eating(t_philo *philo);
int			do_sleeping(t_philo *philo);
int			do_thinking(t_philo *philo);
int			print_action(t_global_info *info, t_action type, int master_index);

/* Philo thread */
int			create_philo_threads(t_philo *head);
int			join_all_threads(t_philo *head);
int			destroy_all_mutex(t_philo *head);

/* Observer */
void		*do_monitoring(void *content);

#endif
