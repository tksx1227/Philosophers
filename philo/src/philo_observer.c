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

#include "philo.h"

static bool	is_everyone_finished_eating(t_philo *head);
static bool	is_anyone_dead(t_philo *head);
static bool	is_finished_eating(t_philo *philo);
static bool	is_dead(t_philo *philo);

void	*do_monitoring(void *content)
{
	t_philo	*head;

	head = (t_philo *)content;
	while (42)
	{
		if (is_everyone_finished_eating(head) || is_anyone_dead(head))
			return (NULL);
		usleep(500);
	}
}

static bool	is_everyone_finished_eating(t_philo *head)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = head;
	while (i < head->info->n_of_philos)
	{
		if (!is_finished_eating(philo))
			return (false);
		philo = philo->next;
		i++;
	}
	pthread_mutex_lock(&head->info->system_status_mutex);
	head->info->is_system_stopped = true;
	pthread_mutex_unlock(&head->info->system_status_mutex);
	return (true);
}

static bool	is_anyone_dead(t_philo *head)
{
	int			i;
	t_philo		*philo;
	t_timestamp	current_time_ms;

	i = 0;
	philo = head;
	while (i < head->info->n_of_philos)
	{
		if (is_dead(philo))
		{
			current_time_ms = get_current_time_us() / 1000;
			pthread_mutex_lock(&philo->info->system_status_mutex);
			printf("%lld %d died\n", current_time_ms, philo->index);
			head->info->is_system_stopped = true;
			pthread_mutex_unlock(&head->info->system_status_mutex);
			return (true);
		}
		philo = philo->next;
		i++;
	}
	return (false);
}

static bool	is_finished_eating(t_philo *philo)
{
	int		max_limit;
	bool	ret;

	ret = false;
	max_limit = philo->info->n_of_times_each_philo_must_eat;
	if (max_limit < 0)
		return (ret);
	pthread_mutex_lock(&philo->info->system_status_mutex);
	if ((size_t)max_limit <= philo->eat_count)
		ret = true;
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	return (ret);
}

static bool	is_dead(t_philo *philo)
{
	bool		ret;
	t_timestamp	current_time_us;
	t_timestamp	time_to_die_us;

	ret = false;
	current_time_us = get_current_time_us();
	time_to_die_us = philo->info->time_to_die * 1000;
	pthread_mutex_lock(&philo->info->system_status_mutex);
	if (time_to_die_us < current_time_us - philo->last_ate_at_us)
		ret = true;
	pthread_mutex_unlock(&philo->info->system_status_mutex);
	return (ret);
}
