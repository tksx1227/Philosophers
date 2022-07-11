/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:35:44 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/08 13:40:35 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	do_eating(t_philo *philo)
{
	if (print_action(philo->info, EATING, philo->index))
		return (1);
	msleep_precise(philo->info->time_to_eat);
	sem_wait(philo->eating_status_sem);
	philo->eat_count++;
	philo->last_ate_at_us = get_current_time_us();
	sem_post(philo->eating_status_sem);
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

	sem_wait(info->print_sem);
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
		return (0);
	}
	sem_post(info->print_sem);
	return (0);
}
