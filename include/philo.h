/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 13:48:53 by ttomori          ###   ########.fr       */
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

typedef long long			t_timestamp;
typedef enum e_status		t_status;
typedef struct s_philo		t_philo;
typedef struct s_philo		t_philo;
typedef struct s_rule		t_rule;
typedef struct s_obs_info	t_obs_info;

struct s_philo
{
	int				index;
	bool			exist_my_fork;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	t_philo			*prev;
	t_philo			*next;
	size_t			eat_count;
	t_timestamp		last_ate_at_us;
	t_rule			*rule;
};

struct s_rule
{
	int		n_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_of_times_each_philo_must_eat;
};

/* Utils */
int			parse_args(int params[], int argc, char **argv);
void		ft_putstr_fd(char const *s, int fd);
void		print_usage(void);
void		init_rule(t_rule *rule, int params[]);
void		msleep(unsigned int ms);
t_timestamp	get_timestamp_us(void);

/* Philo Utils */
t_philo		*get_philos_circular(t_rule *rule);
void		free_philos_circular(t_philo *head);

/* Main Routine */
void		*main_loop(void *content);

#endif
