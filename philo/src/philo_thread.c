/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 09:29:42 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 23:19:02 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads_half(t_philo *head, int start_index);
static void	*main_routine(void *content);

int	create_philo_threads(t_philo *head)
{
	if (create_philo_threads_half(head, 0))
		return (1);
	usleep(CREATE_PHILO_INTERVAL);
	if (create_philo_threads_half(head->next, 1))
		return (1);
	return (0);
}

int	join_all_threads(t_philo *head)
{
	int		i;
	int		n_of_philos;
	t_philo	*philo;

	i = 0;
	philo = head;
	n_of_philos = head->info->n_of_philos;
	while (i < n_of_philos)
	{
		if (pthread_join(philo->thread, NULL))
			return (1);
		philo = philo->next;
		i++;
	}
	return (0);
}

int	destroy_all_mutex(t_philo *head)
{
	int		i;
	int		n_of_philos;
	t_philo	*philo;

	i = 0;
	philo = head;
	n_of_philos = head->info->n_of_philos;
	while (i < n_of_philos)
	{
		if (pthread_mutex_destroy(&philo->fork_mutex))
			return (1);
		philo = philo->next;
		i++;
	}
	return (0);
}

static int	create_philo_threads_half(t_philo *head, int start_index)
{
	long	i;
	long	n_of_philos;
	t_philo	*philo;

	philo = head;
	i = start_index;
	n_of_philos = head->info->n_of_philos;
	while (i < n_of_philos)
	{
		if (pthread_create(&philo->thread, NULL, &main_routine, philo))
			return (1);
		philo = philo->next->next;
		i += 2;
	}
	return (0);
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
			return (NULL);
	}
}
