/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:43:47 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 15:07:08 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_eating(t_philo *philo)
{
	t_timestamp	now_ms;

	pthread_mutex_lock(&philo->info->system_status_mutex);
	if (philo->info->is_system_stopped)
	{
		pthread_mutex_unlock(&philo->info->system_status_mutex);
		return (1);
	}
	now_ms = get_timestamp_us() / 1000;
	printf("%lld %d is eating\n", now_ms, philo->index);
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	msleep(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->system_status_mutex);
	philo->last_ate_at_us = get_timestamp_us();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	return (0);
}

int	do_sleeping(t_philo *philo)
{
	t_timestamp	now_ms;

	pthread_mutex_lock(&philo->info->system_status_mutex);
	if (philo->info->is_system_stopped)
	{
		pthread_mutex_unlock(&philo->info->system_status_mutex);
		return (1);
	}
	now_ms = get_timestamp_us() / 1000;
	printf("%lld %d is sleeping\n", now_ms, philo->index);
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	msleep(philo->info->time_to_sleep);
	return (0);
}

int	do_thinking(t_philo *philo)
{
	t_timestamp	now_ms;

	pthread_mutex_lock(&philo->info->system_status_mutex);
	if (philo->info->is_system_stopped)
	{
		pthread_mutex_unlock(&philo->info->system_status_mutex);
		return (1);
	}
	now_ms = get_timestamp_us() / 1000;
	printf("%lld %d is thinking\n", now_ms, philo->index);
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	return (0);
}
