/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:43:47 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 09:42:25 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_thinking(t_philo *philo)
{
	t_timestamp	now_ms;

	pthread_mutex_lock(&philo->rule->system_status_mutex);
	if (philo->rule->is_finished)
	{
		pthread_mutex_unlock(&philo->rule->system_status_mutex);
		return (1);
	}
	now_ms = get_timestamp_us() / 1000;
	printf("%lld %d is thinking\n", now_ms, philo->index);
	pthread_mutex_unlock(&philo->rule->system_status_mutex);
	return (0);
}
