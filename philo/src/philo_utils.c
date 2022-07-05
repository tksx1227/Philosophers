/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:37:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 15:09:51 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*get_new_philo(int index, t_global_info *info);
static int		add_philo_to_end_of_circular(int index, \
		t_global_info *info, t_philo *head);

int	init_philos_circular(t_philo **head_p, t_global_info *info)
{
	int	i;

	if (info->n_of_philos < 1)
		return (1);
	*head_p = get_new_philo(1, info);
	if (*head_p == NULL)
		return (1);
	(*head_p)->prev = *head_p;
	(*head_p)->next = *head_p;
	i = 1;
	while (i < info->n_of_philos)
	{
		if (add_philo_to_end_of_circular(i + 1, info, *head_p) != 0)
		{
			free_philos_circular(*head_p);
			return (1);
		}
		i++;
	}
	return (0);
}

int	free_philos_circular(t_philo *head)
{
	int		i;
	int		n_of_philos;
	t_philo	*philo;
	t_philo	*tmp;

	if (head == NULL)
		return (1);
	i = 0;
	philo = head;
	n_of_philos = head->info->n_of_philos;
	while (i < n_of_philos)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
	return (0);
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
	philo->prev = NULL;
	philo->next = NULL;
	philo->eat_count = 0;
	philo->last_ate_at_us = get_current_time_us();
	philo->info = info;
	if (pthread_mutex_init(&philo->fork_mutex, NULL))
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
