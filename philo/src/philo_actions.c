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
	if (print_action(philo->info, EATING, philo->index))
	{
		release_two_forks(philo);
		return (1);
	}
	msleep_precise(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->system_status_mutex);
	philo->last_ate_at_us = get_current_time_us();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	return (0);
}

int	do_sleeping(t_philo *philo)
{
	if (print_action(philo->info, SLEEPING, philo->index))
		return (1);
	msleep_precise(philo->info->time_to_sleep);
	return (0);
}

int	do_thinking(t_philo *philo)
{
	return (print_action(philo->info, THINKING, philo->index));
}

int	print_action(t_global_info *info, t_action action, int master_index)
{
	t_timestamp	current_time_ms;

	pthread_mutex_lock(&info->system_status_mutex);
	if (info->is_system_stopped)
	{
		pthread_mutex_unlock(&info->system_status_mutex);
		return (1);
	}
	current_time_ms = get_current_time_us() / 1000;
	if (action == TAKE_A_FORK)
		printf("%lld %d has taken a fork\n", current_time_ms, master_index);
	else if (action == EATING)
		printf("%lld %d is eating\n", current_time_ms, master_index);
	else if (action == SLEEPING)
		printf("%lld %d is sleeping\n", current_time_ms, master_index);
	else if (action == THINKING)
		printf("%lld %d is thinking\n", current_time_ms, master_index);
	else if (action == DEAD)
	{
		printf("%s%lld %d died%s\n", \
			COLOR_RED, current_time_ms, master_index, COLOR_RESET);
		info->is_system_stopped = true;
	}
	pthread_mutex_unlock(&info->system_status_mutex);
	return (0);
}
