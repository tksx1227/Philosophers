/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:37:44 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 15:35:58 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_dead(t_philo *philo);
static bool	is_completed_eating(t_philo *philo);

void	*do_monitoring(void *content)
{
	bool	require_eating_check;
	t_philo	*philo;

	philo = (t_philo *)content;
	require_eating_check = 0 <= philo->info->n_of_times_each_philo_must_eat;
	while (42)
	{
		if (is_dead(philo))
		{
			print_action(philo->info, DEAD, philo->index);
			sem_post(philo->info->someones_death_sem);
			return (NULL);
		}
		if (require_eating_check && is_completed_eating(philo))
		{
			sem_post(philo->info->completed_eating_sem);
			require_eating_check = false;
		}
		usleep(OBSERVE_INTERVAL);
	}
}

static bool	is_completed_eating(t_philo *philo)
{
	int		max_limit;
	size_t	eat_count;

	sem_wait(philo->eating_status_sem);
	eat_count = philo->eat_count;
	sem_post(philo->eating_status_sem);
	max_limit = philo->info->n_of_times_each_philo_must_eat;
	if ((size_t)max_limit <= eat_count)
		return (true);
	return (false);
}

static bool	is_dead(t_philo *philo)
{
	t_timestamp	last_ate_at_us;
	t_timestamp	current_time_us;
	t_timestamp	time_to_die_us;

	sem_wait(philo->eating_status_sem);
	last_ate_at_us = philo->last_ate_at_us;
	sem_post(philo->eating_status_sem);
	current_time_us = get_current_time_us();
	time_to_die_us = (t_timestamp)philo->info->time_to_die * 1000;
	if (time_to_die_us < current_time_us - last_ate_at_us)
		return (true);
	return (false);
}
