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
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <string.h>

# define INITIAL_PID -42
# define OBSERVE_INTERVAL 3000
# define CREATE_PHILO_INTERVAL 2000
# define FORKS_SEM_NAME "/forks"
# define COMPLETED_EATING_SEM_NAME "/completed_eating"
# define PRINT_SEM_NAME "/print"
# define PHILO_SEM_NAME_TEMPLATE "/philosophers_"

typedef long long				t_timestamp;
typedef enum e_action			t_action;
typedef struct s_philo			t_philo;
typedef struct s_global_info	t_global_info;

enum e_exit_status
{
	EXIT_COMPLETED_EATING = 10,
	EXIT_SOMEONE_DIED,
	EXIT_FATAL_ERROR,
};

enum e_action
{
	TAKE_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

struct s_philo
{
	int				index;
	pid_t			pid;
	size_t			eat_count;
	t_philo			*next;
	t_timestamp		last_ate_at_us;
	t_global_info	*info;
	sem_t			*eating_status_sem;
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
size_t		ft_strlen(char *str);
char		*ft_strcpy(char *dst, char *src);
char		*ft_itoa(int n);

/* Philo Semaphore */
int			init_sem(sem_t **sem, const char *name, int init_val);
int			destroy_sem(sem_t **sem, const char *name);
int			init_global_info_sem(t_global_info *info);
int			destroy_global_info_sem(t_global_info *info);
int			destroy_philos_sem(t_philo *head);

/* Philo Process */
int			create_philo_processes(t_philo *philos);
int			create_process_for_monitoring_number_of_meals(t_global_info *info);
int			wait_process(void);
int			kill_all_process(t_philo *philos);

/* Philo Actions */
int			take_two_forks(t_philo *philo);
int			release_two_forks(t_philo *philo);
int			do_eating(t_philo *philo);
int			do_sleeping(t_philo *philo);
int			do_thinking(t_philo *philo);
int			print_action(t_global_info *info, \
		t_action action, int master_index);

/* Philo Utils */
int			init_philos(t_global_info *info, t_philo **head_p);
int			free_all_philos(t_philo **head_p);
char		*get_sem_name(int index);

/* Philo Observer */
void		*do_monitoring(void *content);
void		wait_until_everyone_completed_eating(t_global_info *info);

#endif
