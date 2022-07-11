/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:27:17 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/11 17:44:39 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	kill_process_and_set_init_value(pid_t *pid);

int	wait_any_one_process(void)
{
	int	wstatus;
	int	exit_status_code;

	if (waitpid(-1, &wstatus, 0) == -1)
		return (1);
	if (!WIFEXITED(wstatus))
		return (1);
	exit_status_code = WEXITSTATUS(wstatus);
	if (exit_status_code != EXIT_COMPLETED_EATING && \
		exit_status_code != EXIT_SOMEONE_DIED)
	{
		ft_putstr_fd("FATAL ERROR\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	kill_all_process(t_philo *head)
{
	t_philo	*philo;

	philo = head;
	while (philo != NULL)
	{
		kill_process_and_set_init_value(&philo->pid);
		philo = philo->next;
	}
	kill_process_and_set_init_value(&head->info->eat_count_observer_pid);
	kill_process_and_set_init_value(&head->info->death_observer_pid);
	return (0);
}

static int	kill_process_and_set_init_value(pid_t *pid)
{
	if (pid == NULL)
		return (1);
	if (*pid != INITIAL_PID)
	{
		kill(*pid, SIGKILL);
		*pid = INITIAL_PID;
	}
	return (0);
}
