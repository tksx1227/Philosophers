/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:24:50 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/09 16:23:30 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_philo_process(t_philo *philo);
static int	create_philo_processes_half(t_philo *head, int start_index);

int	create_observer_process(t_global_info *info)
{
	info->eat_count_observer_pid = fork();
	if (info->eat_count_observer_pid < 0)
		return (1);
	else if (info->eat_count_observer_pid == 0)
		wait_until_everyone_completed_eating(info);
	return (0);
}

int	create_philo_processes(t_philo *head)
{
	if (0 <= head->info->eat_count_observer_pid && \
		create_observer_process(head->info))
		return (1);
	if (create_philo_processes_half(head, 0))
	{
		kill_all_process(head);
		return (1);
	}
	usleep(CREATE_PHILO_INTERVAL);
	if (create_philo_processes_half(head->next, 1))
	{
		kill_all_process(head);
		return (1);
	}
	return (0);
}

int	wait_process(void)
{
	int	status;
	int	status_code;

	if (waitpid(-1, &status, 0) == -1)
		return (1);
	if (!WIFEXITED(status))
		return (1);
	status_code = WEXITSTATUS(status);
	if (status_code == EXIT_COMPLETED_EATING || \
		status_code == EXIT_SOMEONE_DIED)
	{
		printf("THE SIMULATION IS COMPLETED...\n");
	}
	return (0);
}

int	kill_all_process(t_philo *philos)
{
	t_philo	*philo;

	philo = philos;
	while (philo != NULL)
	{
		if (philo->pid != INITIAL_PID)
			kill(philo->pid, SIGKILL);
		philo = philo->next;
	}
	return (0);
}

static int	create_philo_processes_half(t_philo *head, int start_index)
{
	int		i;
	t_philo	*philo;

	i = start_index;
	philo = head;
	while (i < head->info->n_of_philos)
	{
		philo->pid = fork();
		if (philo->pid < 0)
			return (1);
		else if (philo->pid == 0)
			start_philo_process(philo);
		if (philo->next == NULL)
			break ;
		philo = philo->next->next;
		i += 2;
	}
	return (0);
}

static void	start_philo_process(t_philo *philo)
{
	pthread_t	philo_thread;
	pthread_t	observer_thread;

	philo->last_ate_at_us = get_current_time_us();
	if (pthread_create(&philo_thread, NULL, &main_routine, philo))
		exit(1);
	if (pthread_create(&observer_thread, NULL, &do_monitoring, philo))
		exit(1);
	if (pthread_join(philo_thread, NULL) || \
		pthread_join(observer_thread, NULL))	
		exit(1);
	exit(0);
}
