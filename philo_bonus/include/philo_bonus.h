/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:28:52 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/09 18:51:32 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <semaphore.h>

# define INITIAL_PID -42
# define FORKS_SEM_NAME "/forks"
# define COMPLETED_EATING_SEM_NAME "/completed_eating"
# define PRINT_SEM_NAME "/print"

typedef long long				t_timestamp;
typedef struct s_philo			t_philo;
typedef struct s_global_info	t_global_info;

struct s_philo
{
	int				index;
	pid_t			pid;
	size_t			eat_count;
	t_philo			*next;
	t_timestamp		last_ate_at_us;
	t_global_info	*info;
};

struct s_global_info
{
	int		n_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_of_times_each_philo_must_eat;
	pid_t	eat_count_observer_pid;
	sem_t	*completed_eating_sem;
	sem_t	*forks_sem;
	sem_t	*print_sem;
};

/* Utils */
int			parse_args(int params[], int argc, char **argv);
int			init_global_info(t_global_info *info, int params[]);
int			msleep_precise(unsigned int ms);
void		print_usage(void);
t_timestamp	get_current_time_us(void);

/* Philo Semaphore */
int			init_sem(sem_t **sem, const char *name, int init_val);
int			destroy_sem(sem_t **sem, const char *name);
int			destroy_all_sem(t_global_info *info);

/* Philo Utils */
int			init_philos(t_global_info *info, t_philo **head_p);
int			free_all_philos(t_philo **head_p);

#endif
