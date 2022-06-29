/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/29 18:46:02 by ttomori          ###   ########.fr       */
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

typedef enum e_status
{
	INIT,
	DIED,
	EATING,
	SLEEPING,
	THINKING,
}	t_status;

typedef struct s_philo
{
	int				index;
	t_status		status;
	bool			exist_my_fork;
	pthread_t		*thread;
	pthread_mutex_t	*fork_mutex;
	t_philo			*next;
	size_t			eat_count;
	t_timestamp		last_ate_at;
}	t_philo;

typedef struct s_gen_info
{
	int	n_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_of_times_each_philo_must_eat;
}	t_gen_info;

/* Utils */
int			parse_args(int params[], int argc, char **argv);
void		ft_putstr_fd(char const *s, int fd);
void		print_usage(void);
void		init_gen_info(t_gen_info *gen_info, int params[]);
t_timestamp	get_timestamp_ms(void);

/* Philo Utils */
t_philo		*get_new_philo(int index);

/* Main Routine */
void		*main_loop(void *content);

#endif
