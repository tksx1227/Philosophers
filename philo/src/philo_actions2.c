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

static int	take_a_fork(int index, t_philo *philo);
static int	return_the_fork(t_philo *philo);

int	take_two_forks(t_philo *philo)
{
	int	index;

	index = philo->index;
	if (take_a_fork(index, philo))
		return (1);
	if (take_a_fork(index, philo->next))
	{
		return_the_fork(philo);
		return (1);
	}
	return (0);
}

int	return_two_forks(t_philo *philo)
{
	if (return_the_fork(philo) || return_the_fork(philo->next))
		return (1);
	return (0);
}

static int	take_a_fork(int index, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->info->system_status_mutex);
	if (philo->info->is_system_stopped)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->info->system_status_mutex);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_current_time_us() / 1000, index);
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	return (0);
}

static int	return_the_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_mutex);
	return (0);
}
