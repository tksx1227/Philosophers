/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:22:55 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/10 16:23:13 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process_for_monitoring_number_of_meals(t_global_info *info)
{
	info->eat_count_observer_pid = fork();
	if (info->eat_count_observer_pid < 0)
		return (1);
	else if (info->eat_count_observer_pid == 0)
		wait_until_everyone_completed_eating(info);
	return (0);
}

int	wait_process(void)
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
		return (1);
	printf("THE SIMULATION IS COMPLETED...\n");
	return (0);
}

int	kill_all_process(t_philo *head)
{
	t_philo	*philo;

	philo = head;
	while (philo != NULL)
	{
		if (philo->pid != INITIAL_PID)
		{
			kill(philo->pid, SIGKILL);
			philo->pid = INITIAL_PID;
		}
		philo = philo->next;
	}
	if (head->info->eat_count_observer_pid != INITIAL_PID)
	{
		kill(head->info->eat_count_observer_pid, SIGKILL);
		head->info->eat_count_observer_pid = INITIAL_PID;
	}
	return (0);
}
