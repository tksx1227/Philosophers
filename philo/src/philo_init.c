/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:37:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 15:07:28 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*get_new_philo(int index, t_global_info *info);
static int		add_philo_to_end_of_circular(int index, \
		t_global_info *info, t_philo *head);

t_philo	*get_philos_circular(t_global_info *info)
{
	int		i;
	t_philo	*head;

	if (info->n_of_philos < 1)
		return (NULL);
	i = 1;
	head = get_new_philo(1, info);
	if (head == NULL)
		return (NULL);
	head->prev = head;
	head->next = head;
	while (i < info->n_of_philos)
	{
		if (add_philo_to_end_of_circular(i + 1, info, head) != 0)
		{
			free_philos_circular(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

static int	add_philo_to_end_of_circular(int index, \
		t_global_info *info, t_philo *head)
{
	t_philo	*philo;

	philo = get_new_philo(index, info);
	if (philo == NULL)
		return (1);
	philo->prev = head->prev;
	philo->next = head;
	head->prev->next = philo;
	head->prev = philo;
	return (0);
}

static t_philo	*get_new_philo(int index, t_global_info *info)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->index = index;
	philo->exist_my_fork = true;
	philo->prev = NULL;
	philo->next = NULL;
	philo->eat_count = 0;
	philo->last_ate_at_us = get_timestamp_us();
	philo->info = info;
	if (pthread_mutex_init(&philo->fork_mutex, NULL))
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
