/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:24:50 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/10 17:21:29 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*main_routine(void *content);
static void	start_philo_process(t_philo *philo);
static int	create_half_of_philo_processes(t_philo *head, int start_index);

int	create_philo_processes(t_philo *head)
{
	if (0 <= head->info->n_of_times_each_philo_must_eat && \
		create_process_for_monitoring_number_of_meals(head->info))
		return (1);
	if (create_half_of_philo_processes(head, 0))
	{
		kill_all_process(head);
		return (1);
	}
	usleep(CREATE_PHILO_INTERVAL);
	if (create_half_of_philo_processes(head->next, 1))
	{
		kill_all_process(head);
		return (1);
	}
	return (0);
}

static int	create_half_of_philo_processes(t_philo *head, int start_index)
{
	int		i;
	t_philo	*philo;

	if (head == NULL)
		return (0);
	i = start_index;
	philo = head;
	while (i < head->info->n_of_philos)
	{
		philo->pid = fork();
		if (philo->pid < 0)
			return (1);
		else if (philo->pid == 0)
			start_philo_process(philo);
		if (philo->next == NULL)
			break ;
		philo = philo->next->next;
		i += 2;
	}
	return (0);
}

static void	start_philo_process(t_philo *philo)
{
	pthread_t	philo_thread;
	pthread_t	observer_thread;

	philo->last_ate_at_us = get_current_time_us();
	if (pthread_create(&philo_thread, NULL, &main_routine, philo) || \
		pthread_create(&observer_thread, NULL, &do_monitoring, philo))
		exit(1);
	if (pthread_join(philo_thread, NULL) || \
		pthread_join(observer_thread, NULL))
		exit(1);
	exit(0);
}

static void	*main_routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	while (42)
	{
		if (take_two_forks(philo) \
				|| do_eating(philo) \
				|| release_two_forks(philo) \
				|| do_sleeping(philo) \
				|| do_thinking(philo))
			exit(1);
	}
}
