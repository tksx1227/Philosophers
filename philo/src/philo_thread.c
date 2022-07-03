/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 09:29:42 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 15:36:29 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*main_routine(void *content);

int	create_philo_threads(t_philo *head)
{
	int		i;
	int		n_of_philos;
	t_philo	*philo;

	i = 0;
	philo = head;
	n_of_philos = head->info->n_of_philos;
	while (i < n_of_philos)
	{
		if (pthread_create(&philo->thread, NULL, &main_routine, philo))
			return (1);
		philo = philo->next;
		i++;
	}
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

static void	*main_routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	while (!philo->info->is_setup_completed)
		;
	if (philo->index % 2 == 0)
		usleep(300);
	while (42)
	{
		if (take_two_forks(philo) \
			|| do_eating(philo) \
			|| return_two_forks(philo) \
			|| do_sleeping(philo) \
			|| do_thinking(philo))
			return (NULL);
	}
}
