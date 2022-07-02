/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:13:43 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 09:42:52 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	return_the_fork(t_philo *philo);

int	return_two_forks(t_philo *philo)
{
	if (return_the_fork(philo) || return_the_fork(philo->next))
		return (1);
	return (0);
}

static int	return_the_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->system_status_mutex);
	if (philo->rule->is_finished)
	{
		pthread_mutex_unlock(&philo->rule->system_status_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->fork_mutex);
	philo->exist_my_fork = true;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->rule->system_status_mutex);
	return (0);
}
