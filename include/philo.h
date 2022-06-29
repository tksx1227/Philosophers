/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/29 23:47:19 by ttomori          ###   ########.fr       */
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

typedef unsigned long long	t_timestamp;
typedef enum e_status		t_status;
typedef struct s_philo		t_philo;
typedef struct s_philo		t_philo;
typedef struct s_rule		t_rule;
typedef struct s_obs_info	t_obs_info;

enum e_status
{
	INIT,
	DIED,
	EATING,
	SLEEPING,
	THINKING,
};

struct s_philo
{
	int				index;
	t_status		status;
	bool			exist_my_fork;
	pthread_t		*thread;
	pthread_mutex_t	*fork_mutex;
	t_philo			*next;
	size_t			eat_count;
	t_timestamp		last_ate_at;
};

struct s_rule
{
	int	n_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_of_times_each_philo_must_eat;
};

struct s_obs_info
{
	t_philo		*head;
	t_rule		*rule;
};

/* Utils */
int			parse_args(int params[], int argc, char **argv);
void		ft_putstr_fd(char const *s, int fd);
void		print_usage(void);
void		init_rule(t_rule *rule, int params[]);
t_timestamp	get_timestamp_ms(void);

/* Philo Utils */
t_philo		*get_new_philo(int index);
void		free_philos_circular(t_philo *head);

/* Main Routine */
void		*main_loop(void *content);

#endif
