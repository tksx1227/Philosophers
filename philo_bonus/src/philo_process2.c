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

static void	wait_until_someone_died(t_global_info *info);
static void	wait_until_everyone_completed_eating(t_global_info *info);

int	create_process_for_monitoring_someones_death(t_global_info *info)
{
	info->death_observer_pid = fork();
	if (info->death_observer_pid < 0)
		return (1);
	else if (info->death_observer_pid == 0)
		wait_until_someone_died(info);
	return (0);
}

int	create_process_for_monitoring_number_of_meals(t_global_info *info)
{
	info->eat_count_observer_pid = fork();
	if (info->eat_count_observer_pid < 0)
		return (1);
	else if (info->eat_count_observer_pid == 0)
		wait_until_everyone_completed_eating(info);
	return (0);
}

static void	wait_until_someone_died(t_global_info *info)
{
	sem_wait(info->someones_death_sem);
	exit(EXIT_SOMEONE_DIED);
}

static void	wait_until_everyone_completed_eating(t_global_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_of_philos)
	{
		sem_wait(info->completed_eating_sem);
		i++;
	}
	sem_wait(info->print_sem);
	exit(EXIT_COMPLETED_EATING);
}
