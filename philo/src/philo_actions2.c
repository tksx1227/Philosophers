/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:13:43 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 15:07:17 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_a_fork(int master_index, t_philo *philo);
static int	release_a_fork(t_philo *philo);
static void	wait_until_system_stop(t_global_info *info);

int	take_two_forks(t_philo *philo)
{
	int	index;

	index = philo->index;
	if (take_a_fork(index, philo))
		return (1);
	if (philo->info->n_of_philos == 1)
	{
		wait_until_system_stop(philo->info);
		release_a_fork(philo);
		return (1);
	}
	if (take_a_fork(index, philo->next))
	{
		release_a_fork(philo);
		return (1);
	}
	return (0);
}

int	release_two_forks(t_philo *philo)
{
	if (release_a_fork(philo) || release_a_fork(philo->next))
		return (1);
	return (0);
}

static int	take_a_fork(int master_index, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (print_action(philo->info, TAKE_A_FORK, master_index))
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		return (1);
	}
	return (0);
}

static int	release_a_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_mutex);
	return (0);
}

static void	wait_until_system_stop(t_global_info *info)
{
	bool	is_system_stopped;

	while (42)
	{
		pthread_mutex_lock(&info->system_status_mutex);
		is_system_stopped = info->is_system_stopped;
		pthread_mutex_unlock(&info->system_status_mutex);
		if (is_system_stopped)
			return ;
		usleep(100);
	}
}
